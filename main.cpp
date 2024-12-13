// main.cpp

#include "packet_capture.h"
#include "flow_feature_extraction.h"
#include "normalization.h"
#include "classification.h"
#include "data_storage.h"
#include "sdn_dataset_loader.h" 
#include <iostream>

int main() {
    // Step 1: Load CICDDoS2019 dataset for training
    std::vector<FlowData> dataset = load_sdn_dataset("ISCX_SDN.csv");

    // Step 2: Normalize the dataset
    normalize_dataset(dataset);

    // Step 3: Train the model using the dataset
    train_model(dataset);  // Store the model to be used in real-time classification

    // Step 4: Capture packets from the network in real-time (optional for testing)
    capture_packets("eth0");

    // Step 5: Extract flow features (from real-time packet capture)
    FlowFeatures features = extract_features_from_dataset(dataset);

    // Step 6: Normalize extracted features
    double avg_packet_size = (features.max_packet_len+features.min_packet_len)/2;
    std::vector<double> feature_values = { 
    static_cast<double>(features.max_packet_len), 
    static_cast<double>(features.min_packet_len), 
    static_cast<double>(avg_packet_size)  // No need to cast this if it's already double
    };
    normalize(feature_values);

    // Step 7: Classify traffic using the trained model
    classify_traffic(feature_values);

    // Step 8: Save data to CSV (for analysis or retraining)
    std::vector<FlowFeatures> all_features = { features };
    save_to_csv(all_features, "output.csv");

    return 0;
}