// // flow_feature_extraction.h
// #ifndef FLOW_FEATURE_EXTRACTION_H
// #define FLOW_FEATURE_EXTRACTION_H

// #include <vector>

// struct Packet {};  // Define your Packet structure here
// struct FlowFeatures {
//     int max_packet_len;
//     int min_packet_len;
//     double avg_packet_size;
//     double avg_inter_arrival_time;
// };

// // New structure for the dataset rows (features + label)
// struct FlowData {
//     int max_packet_len;
//     int min_packet_len;
//     double avg_packet_size;
//     double inter_arrival_time;  // New feature for SDN environments
//     int label;  // Label for classification: 0 = benign, 1 = DDoS attack, etc.
// };

// // Function to extract flow features from captured packets
// FlowFeatures extract_features(const std::vector<Packet>& flow_packets);

// // Function to extract features directly from dataset rows
// FlowFeatures extract_features_from_dataset(const std::vector<FlowData>& flow_data);

// #endif

// flow_feature_extraction.h
#ifndef FLOW_FEATURE_EXTRACTION_H
#define FLOW_FEATURE_EXTRACTION_H

#include <vector>

struct Packet {};  // Define your Packet structure here
struct FlowFeatures {
    int max_packet_len;
    int min_packet_len;
    double mean_packet_len;
    double packet_len_std_dev;
    double fwd_packet_len_mean;
    double fwd_packet_len_std_dev;
    double bwd_packet_len_mean;
    double bwd_packet_len_std_dev;
    int flow_duration;
    int total_fwd_packets;
    int total_bwd_packets;
    int total_fwd_bytes;
    int total_bwd_bytes;
    double fwd_inter_arrival_time_mean;
    double bwd_inter_arrival_time_mean;
    double flow_inter_arrival_time_std_dev;
    double flow_byte_rate;
    double flow_packet_rate;
    int fwd_header_length;
    int bwd_header_length;
    int ack_packet_count;
};

struct FlowData {
    FlowFeatures features;
    int label;  // 0 = benign, 1 = attack
};

// Function to extract flow features from captured packets
FlowFeatures extract_features(const std::vector<Packet>& flow_packets);

// Function to extract features directly from dataset rows
FlowFeatures extract_features_from_dataset(const std::vector<FlowData>& flow_data);

#endif
