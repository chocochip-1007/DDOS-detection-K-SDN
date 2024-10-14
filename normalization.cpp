// normalization.cpp

#include "normalization.h"
#include <algorithm>
#include <vector>

void normalize(std::vector<double>& features) {
    double min_val = *std::min_element(features.begin(), features.end());
    double max_val = *std::max_element(features.begin(), features.end());

    for (auto& feature : features) {
        feature = (feature - min_val) / (max_val - min_val);  // Normalize between 0 and 1
    }
}