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

FlowFeatures extract_features(const std::vector<Packet>& flow_packets);

#endif