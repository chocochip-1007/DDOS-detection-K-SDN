// data_storage.h
#ifndef DATA_STORAGE_H
#define DATA_STORAGE_H

#include "flow_feature_extraction.h"
#include <vector>
#include <string>

void save_to_csv(const std::vector<FlowFeatures>& features, const std::string& filename);

#endif