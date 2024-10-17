#include <fstream>
#include <vector>
#include <sstream>
#include <iostream>
#include "dataset_loader.h"

std::vector<FlowData> load_dataset(const std::string& filename) {
    std::vector<FlowData> dataset;
    std::ifstream file(filename);
    std::string line, value;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        FlowData data;
        std::getline(ss, value, ',');
        data.max_packet_len = std::stod(value);
        std::getline(ss, value, ',');
        data.min_packet_len = std::stod(value);
        std::getline(ss, value, ',');
        data.avg_packet_size = std::stod(value);
        std::getline(ss, value, ',');
        data.label = std::stoi(value);  // Benign or Attack (label for classification)
        dataset.push_back(data);
    }
    return dataset;
}