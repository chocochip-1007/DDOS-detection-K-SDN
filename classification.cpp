#include "classification.h"
#include <mlpack/core.hpp>
#include <mlpack/methods/random_forest/random_forest.hpp>
#include <armadillo>
#include <iostream>

// Function to classify real-time traffic using the pre-trained model
void classify_traffic(const std::vector<double>& features) {
    arma::mat data;
    data.set_size(14, 1);  // Adjusted for 14 features
    for (size_t i = 0; i < features.size(); ++i) {
        data(i, 0) = features[i];
    }

    mlpack::regression::RandomForest<> rfModel;
    mlpack::data::Load("rf_model.xml", "RandomForestModel", rfModel);

    arma::Row<size_t> predictions;
    rfModel.Classify(data, predictions);

    std::cout << "Classified as: " << predictions(0) << std::endl;
}

// Function to train the model using the dataset
void train_model(const std::vector<FlowData>& dataset) {
    arma::mat data(14, dataset.size());  // Adjusted for 14 features
    arma::Row<size_t> labels(dataset.size());

    for (size_t i = 0; i < dataset.size(); ++i) {
        const auto& features = dataset[i].features;
        data.col(i) = arma::vec({
            static_cast<double>(features.max_packet_len),
            static_cast<double>(features.min_packet_len),
            features.mean_packet_len,
            features.fwd_packet_len_mean,
            features.bwd_packet_len_mean,
            static_cast<double>(features.total_fwd_packets),
            static_cast<double>(features.total_bwd_packets),
            static_cast<double>(features.total_fwd_bytes),
            static_cast<double>(features.total_bwd_bytes),
            features.flow_byte_rate,
            features.flow_packet_rate,
            static_cast<double>(features.flow_duration),
            static_cast<double>(features.ack_packet_count)
        });
        labels(i) = dataset[i].label;
    }

    mlpack::regression::RandomForest<> rfModel;
    rfModel.Train(data, labels, 2);  // Assuming binary classification: benign or attack
    mlpack::data::Save("rf_model.xml", "RandomForestModel", rfModel);
}
