// classification.cpp

#include "classification.h"
#include <mlpack/core.hpp>
#include <mlpack/methods/random_forest/random_forest.hpp>
#include <iostream>

void classify_traffic(const std::vector<double>& features) {
    arma::mat data;
    mlpack::data::Load("model.xml", "RandomForestModel", data);  // Load the pre-trained model

    arma::Row<size_t> predictions;
    mlpack::regression::RandomForest<> rfModel;
    rfModel.Classify(data, predictions);

    std::cout << "Class: " << predictions(0) << std::endl;
}