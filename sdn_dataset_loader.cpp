// sdn_dataset_loader.cpp
#include <fstream>
#include <vector>
#include <sstream>
#include <iostream>
#include <limits>
#include "sdn_dataset_loader.h"

std::vector<FlowData> load_sdn_dataset(const std::string& filename) {
    std::vector<FlowData> dataset;
    std::ifstream file(filename);
    std::string line, value;

    // Skip the header row if the dataset contains column names
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        FlowData data;

        // Extract features from ISCX_SDN dataset
        // Assuming the dataset provides the following columns:
        // max_packet_len, min_packet_len, total_fwd_bytes, total_bwd_bytes, 
        // total_fwd_packets, total_bwd_packets, flow_duration, ack_packet_count
        
        std::getline(ss, value, ',');
        data.features.max_packet_len = std::stoi(value);

        std::getline(ss, value, ',');
        data.features.min_packet_len = std::stoi(value);

        std::getline(ss, value, ',');
        data.features.total_fwd_bytes = std::stoi(value);

        std::getline(ss, value, ',');
        data.features.total_bwd_bytes = std::stoi(value);

        std::getline(ss, value, ',');
        data.features.total_fwd_packets = std::stoi(value);

        std::getline(ss, value, ',');
        data.features.total_bwd_packets = std::stoi(value);

        std::getline(ss, value, ',');
        data.features.flow_duration = std::stoi(value);

        std::getline(ss, value, ',');
        data.features.ack_packet_count = std::stoi(value);

        // Compute derived features
        if (data.features.total_fwd_packets > 0) {
            data.features.fwd_packet_len_mean = static_cast<double>(data.features.total_fwd_bytes) / data.features.total_fwd_packets;
        } else {
            data.features.fwd_packet_len_mean = 0.0;
        }

        if (data.features.total_bwd_packets > 0) {
            data.features.bwd_packet_len_mean = static_cast<double>(data.features.total_bwd_bytes) / data.features.total_bwd_packets;
        } else {
            data.features.bwd_packet_len_mean = 0.0;
        }

        data.features.mean_packet_len = (data.features.total_fwd_bytes + data.features.total_bwd_bytes) /
                                         (data.features.total_fwd_packets + data.features.total_bwd_packets);

        data.features.flow_byte_rate = (data.features.total_fwd_bytes + data.features.total_bwd_bytes) /
                                        static_cast<double>(data.features.flow_duration);

        data.features.flow_packet_rate = (data.features.total_fwd_packets + data.features.total_bwd_packets) /
                                          static_cast<double>(data.features.flow_duration);

        // Populate label (assuming last column contains the label)
        std::getline(ss, value, ',');
        data.label = std::stoi(value);  // Label: 0 = benign, 1 = attack

        dataset.push_back(data);
    }

    return dataset;
}
