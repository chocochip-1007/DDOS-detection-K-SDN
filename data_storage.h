// data_storage.h
#ifndef DATA_STORAGE_H
#define DATA_STORAGE_H

#include <string>
#include <vector>
#include "flow_feature_extraction.h"

// Function to save extracted features to a CSV file
void save_to_csv(const std::vector<FlowFeatures>& features, const std::string& filename);

#endif