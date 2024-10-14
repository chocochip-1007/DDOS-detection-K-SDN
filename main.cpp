// main.cpp

#include "packet_capture.h"
#include "flow_feature_extraction.h"
#include "normalization.h"
#include "classification.h"
#include "data_storage.h"
#include <iostream>

int main() {
    // Capture packets from network
    capture_packets("eth0");

    // Extract flow features (this will be processed from captured packets)
    std::vector<Packet> flow_packets;  // This should come from packet capture
    FlowFeatures features = extract_features(flow_packets);

    // Normalize features
    std::vector<double> feature_values = { features.max_packet_len, features.min_packet_len, features.avg_packet_size };
    normalize(feature_values);

    // Classify traffic using pre-trained model
    classify_traffic(feature_values);

    // Store data to CSV
    std::vector<FlowFeatures> all_features = { features };
    save_to_csv(all_features, "output.csv");

    return 0;
}