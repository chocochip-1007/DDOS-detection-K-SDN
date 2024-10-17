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

FlowFeatures extract_features_from_dataset(const FlowData& flow) {
    FlowFeatures features;
    features.max_packet_len = flow.max_packet_len;
    features.min_packet_len = flow.min_packet_len;
    features.avg_packet_size = flow.avg_packet_size;
    return features;
}