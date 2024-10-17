#include "classification.h"
#include <mlpack/core.hpp>
#include <mlpack/methods/random_forest/random_forest.hpp>
#include <iostream>
#include <armadillo>

// Function to classify real-time traffic using the pre-trained model
void classify_traffic(const std::vector<double>& features) {
    arma::mat data;
    data.set_size(3, 1);  // Assuming 3 features (e.g., max_packet_len, min_packet_len, avg_packet_size)
    data(0, 0) = features[0];
    data(1, 0) = features[1];
    data(2, 0) = features[2];

    mlpack::regression::RandomForest<> rfModel;
    mlpack::data::Load("rf_model.xml", "RandomForestModel", rfModel);  // Load the pre-trained Random Forest model

    arma::Row<size_t> predictions;
    rfModel.Classify(data, predictions);

    std::cout << "Classified as: " << predictions(0) << std::endl;
}

// Function to train the model using the dataset
void train_model(const std::vector<FlowData>& dataset) {
    arma::mat data;  // Feature matrix
    arma::Row<size_t> labels;  // Labels for classification

    // Prepare data for mlpack (convert dataset to matrix form)
    data.set_size(3, dataset.size());  // Assuming 3 features
    labels.set_size(dataset.size());

    for (size_t i = 0; i < dataset.size(); ++i) {
        data(0, i) = dataset[i].max_packet_len;
        data(1, i) = dataset[i].min_packet_len;
        data(2, i) = dataset[i].avg_packet_size;
        labels(i) = dataset[i].label;
    }

    // Train the Random Forest model
    mlpack::regression::RandomForest<> rfModel;
    rfModel.Train(data, labels, 3);  // Number of classes (for example: benign, DDoS type 1, DDoS type 2)

    // Save the trained model to a file
    mlpack::data::Save("rf_model.xml", "RandomForestModel", rfModel);
}