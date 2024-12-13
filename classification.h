// classification.h
#ifndef CLASSIFICATION_H
#define CLASSIFICATION_H

#include <vector>
#include "flow_feature_extraction.h"

// Function to classify traffic based on features using a pre-trained model
void classify_traffic(const std::vector<double>& features);

// Function to train the Random Forest model with the dataset and save it
void train_model(const std::vector<FlowData>& dataset);

#endif  // CLASSIFICATION_H_