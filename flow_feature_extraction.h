// flow_feature_extraction.h
#ifndef FLOW_FEATURE_EXTRACTION_H
#define FLOW_FEATURE_EXTRACTION_H

#include <vector>

struct Packet {};  // Define your Packet structure here
struct FlowFeatures {
    int max_packet_len;
    int min_packet_len;
    double avg_packet_size;
};

// New structure for the dataset rows (features + label)
struct FlowData {
    int max_packet_len;
    int min_packet_len;
    double avg_packet_size;
    int label;  // Label for classification: 0 = benign, 1 = DDoS attack, etc.
};

// Function to extract flow features from captured packets
FlowFeatures extract_features(const std::vector<Packet>& flow_packets);

// Function to extract features directly from dataset rows
FlowFeatures extract_features_from_dataset(const FlowData& flow);

#endif