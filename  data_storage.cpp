// data_storage.cpp

#include "data_storage.h"
#include <fstream>
#include <iostream>

void save_to_csv(const std::vector<FlowFeatures>& features, const std::string& filename) {
    std::ofstream file(filename);
    
    for (const auto& feature : features) {
        file << feature.max_packet_len << "," << feature.min_packet_len << "," << feature.avg_packet_size << "\n";
    }

    file.close();
}