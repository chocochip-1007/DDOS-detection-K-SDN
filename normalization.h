// normalization.h
#ifndef NORMALIZATION_H
#define NORMALIZATION_H

#include <vector>
#include "flow_feature_extraction.h"

// Function to normalize individual feature vectors
void normalize(std::vector<double>& features);

// Function to normalize an entire dataset (FlowData structure)
void normalize_dataset(std::vector<FlowData>& dataset);

#endif