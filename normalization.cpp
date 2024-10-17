// normalization.cpp

#include "normalization.h"
#include <algorithm>
#include <vector>

void normalize(std::vector<double>& features) {
    double min_val = *std::min_element(features.begin(), features.end());
    double max_val = *std::max_element(features.begin(), features.end());

    for (auto& feature : features) {
        feature = (feature - min_val) / (max_val - min_val);
    }
}

void normalize_dataset(std::vector<FlowData>& dataset) {
    double global_max_val = std::numeric_limits<double>::lowest();
    double global_min_val = std::numeric_limits<double>::max();
    
    // Find global min and max for normalization
    for (const auto& flow : dataset) {
        // Ensure all values are treated as double to avoid type mismatch
        double max_packet_len = static_cast<double>(flow.max_packet_len);
        double min_packet_len = static_cast<double>(flow.min_packet_len);
        double avg_packet_size = static_cast<double>(flow.avg_packet_size);

        // Update max and min values across all features
        global_max_val = std::max(global_max_val, std::max(max_packet_len, std::max(min_packet_len, avg_packet_size)));
        global_min_val = std::min(global_min_val, std::min(max_packet_len, std::min(min_packet_len, avg_packet_size)));
    }

    // Normalize the dataset
    for (auto& flow : dataset) {
        flow.max_packet_len = (flow.max_packet_len - global_min_val) / (global_max_val - global_min_val);
        flow.min_packet_len = (flow.min_packet_len - global_min_val) / (global_max_val - global_min_val);
        flow.avg_packet_size = (flow.avg_packet_size - global_min_val) / (global_max_val - global_min_val);
    }
}