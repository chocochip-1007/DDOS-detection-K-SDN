// flow_feature_extraction.cpp

#include "flow_feature_extraction.h"
#include <iostream>
#include <vector>

FlowFeatures extract_features(const std::vector<Packet>& flow_packets) {
    FlowFeatures features;
    
    // Replace this logic with real-time extraction logic from packets
    features.max_packet_len = 1000;  // Example placeholder logic
    features.min_packet_len = 40;
    features.avg_packet_size = 512.5;
    
    return features;
}

FlowFeatures extract_features_from_dataset(const std::vector<FlowData>& flow_data) {
    FlowFeatures features;

    // Initialize min and max values
    features.max_packet_len = 0;
    features.min_packet_len = INT_MAX;  // Initialize to a very high value
    double total_packet_size = 0.0;

    // Loop through the vector to calculate the max, min, and total average packet size
    for (const auto& flow : flow_data) {
        // Find the maximum packet length
        if (flow.max_packet_len > features.max_packet_len) {
            features.max_packet_len = flow.max_packet_len;
        }

        // Find the minimum packet length
        if (flow.min_packet_len < features.min_packet_len) {
            features.min_packet_len = flow.min_packet_len;
        }

        // Accumulate total packet size for calculating average
        total_packet_size += flow.avg_packet_size;
    }

    // Calculate average packet size
    if (!flow_data.empty()) {
        features.avg_packet_size = total_packet_size / flow_data.size();
    } else {
        features.avg_packet_size = 0;  // Avoid division by zero
    }

    return features;
}