#include "data_storage.h"
#include <fstream>
#include <iostream>

void save_to_csv(const std::vector<FlowFeatures>& features, const std::string& filename) {
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << " for writing." << std::endl;
        return;
    }

    // Write header row
    file << "max_packet_len,min_packet_len,mean_packet_len,fwd_packet_len_mean,bwd_packet_len_mean,"
         << "total_fwd_packets,total_bwd_packets,total_fwd_bytes,total_bwd_bytes,flow_byte_rate,"
         << "flow_packet_rate,flow_duration,ack_packet_count\n";

    // Write feature values for each flow
    for (const auto& feature : features) {
        file << feature.max_packet_len << ","
             << feature.min_packet_len << ","
             << feature.mean_packet_len << ","
             << feature.fwd_packet_len_mean << ","
             << feature.bwd_packet_len_mean << ","
             << feature.total_fwd_packets << ","
             << feature.total_bwd_packets << ","
             << feature.total_fwd_bytes << ","
             << feature.total_bwd_bytes << ","
             << feature.flow_byte_rate << ","
             << feature.flow_packet_rate << ","
             << feature.flow_duration << ","
             << feature.ack_packet_count << "\n";
    }

    file.close();
    std::cout << "Data successfully saved to " << filename << std::endl;
}
