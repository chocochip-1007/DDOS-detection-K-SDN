#include "normalization.h"
#include <algorithm>
#include <vector>
#include <limits>

void normalize(std::vector<double>& features) {
    double min_val = *std::min_element(features.begin(), features.end());
    double max_val = *std::max_element(features.begin(), features.end());

    for (auto& feature : features) {
        feature = (feature - min_val) / (max_val - min_val);
    }
}

void normalize_dataset(std::vector<FlowData>& dataset) {
    // Initialize global min and max values
    double global_max_val = std::numeric_limits<double>::lowest();
    double global_min_val = std::numeric_limits<double>::max();

    // Step 1: Find global min and max values for all features
    for (const auto& flow : dataset) {
        global_max_val = std::max(global_max_val, static_cast<double>(flow.features.max_packet_len));
        global_max_val = std::max(global_max_val, static_cast<double>(flow.features.min_packet_len));
        global_max_val = std::max(global_max_val, flow.features.mean_packet_len);
        global_max_val = std::max(global_max_val, flow.features.fwd_packet_len_mean);
        global_max_val = std::max(global_max_val, flow.features.bwd_packet_len_mean);
        global_max_val = std::max(global_max_val, static_cast<double>(flow.features.total_fwd_packets));
        global_max_val = std::max(global_max_val, static_cast<double>(flow.features.total_bwd_packets));
        global_max_val = std::max(global_max_val, static_cast<double>(flow.features.total_fwd_bytes));
        global_max_val = std::max(global_max_val, static_cast<double>(flow.features.total_bwd_bytes));
        global_max_val = std::max(global_max_val, flow.features.flow_byte_rate);
        global_max_val = std::max(global_max_val, flow.features.flow_packet_rate);
        global_max_val = std::max(global_max_val, static_cast<double>(flow.features.flow_duration));
        global_max_val = std::max(global_max_val, static_cast<double>(flow.features.ack_packet_count));

        global_min_val = std::min(global_min_val, static_cast<double>(flow.features.max_packet_len));
        global_min_val = std::min(global_min_val, static_cast<double>(flow.features.min_packet_len));
        global_min_val = std::min(global_min_val, flow.features.mean_packet_len);
        global_min_val = std::min(global_min_val, flow.features.fwd_packet_len_mean);
        global_min_val = std::min(global_min_val, flow.features.bwd_packet_len_mean);
        global_min_val = std::min(global_min_val, static_cast<double>(flow.features.total_fwd_packets));
        global_min_val = std::min(global_min_val, static_cast<double>(flow.features.total_bwd_packets));
        global_min_val = std::min(global_min_val, static_cast<double>(flow.features.total_fwd_bytes));
        global_min_val = std::min(global_min_val, static_cast<double>(flow.features.total_bwd_bytes));
        global_min_val = std::min(global_min_val, flow.features.flow_byte_rate);
        global_min_val = std::min(global_min_val, flow.features.flow_packet_rate);
        global_min_val = std::min(global_min_val, static_cast<double>(flow.features.flow_duration));
        global_min_val = std::min(global_min_val, static_cast<double>(flow.features.ack_packet_count));
    }

    // Step 2: Normalize the dataset
    for (auto& flow : dataset) {
        flow.features.max_packet_len = (flow.features.max_packet_len - global_min_val) / (global_max_val - global_min_val);
        flow.features.min_packet_len = (flow.features.min_packet_len - global_min_val) / (global_max_val - global_min_val);
        flow.features.mean_packet_len = (flow.features.mean_packet_len - global_min_val) / (global_max_val - global_min_val);
        flow.features.fwd_packet_len_mean = (flow.features.fwd_packet_len_mean - global_min_val) / (global_max_val - global_min_val);
        flow.features.bwd_packet_len_mean = (flow.features.bwd_packet_len_mean - global_min_val) / (global_max_val - global_min_val);
        flow.features.total_fwd_packets = (flow.features.total_fwd_packets - global_min_val) / (global_max_val - global_min_val);
        flow.features.total_bwd_packets = (flow.features.total_bwd_packets - global_min_val) / (global_max_val - global_min_val);
        flow.features.total_fwd_bytes = (flow.features.total_fwd_bytes - global_min_val) / (global_max_val - global_min_val);
        flow.features.total_bwd_bytes = (flow.features.total_bwd_bytes - global_min_val) / (global_max_val - global_min_val);
        flow.features.flow_byte_rate = (flow.features.flow_byte_rate - global_min_val) / (global_max_val - global_min_val);
        flow.features.flow_packet_rate = (flow.features.flow_packet_rate - global_min_val) / (global_max_val - global_min_val);
        flow.features.flow_duration = (flow.features.flow_duration - global_min_val) / (global_max_val - global_min_val);
        flow.features.ack_packet_count = (flow.features.ack_packet_count - global_min_val) / (global_max_val - global_min_val);
    }
}
