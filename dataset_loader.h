// dataset_loader.h
#ifndef DATASET_LOADER_H
#define DATASET_LOADER_H

#include <string>
#include <vector>
#include "flow_feature_extraction.h"

// Function to load the dataset from a CSV file
std::vector<FlowData> load_dataset(const std::string& filename);

#endif