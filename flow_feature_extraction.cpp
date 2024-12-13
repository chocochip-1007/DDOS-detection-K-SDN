#include "flow_feature_extraction.h"
#include <cmath>
#include <numeric>
#include <limits>

FlowFeatures extract_features_from_dataset(const std::vector<FlowData>& flow_data) {
    FlowFeatures features = {};

    // Initialize default values
    features.max_packet_len = std::numeric_limits<int>::min();
    features.min_packet_len = std::numeric_limits<int>::max();
    features.mean_packet_len = 0.0;
    features.fwd_packet_len_mean = 0.0;
    features.bwd_packet_len_mean = 0.0;
    features.flow_duration = 0;
    features.total_fwd_packets = 0;
    features.total_bwd_packets = 0;
    features.total_fwd_bytes = 0;
    features.total_bwd_bytes = 0;
    features.flow_byte_rate = 0.0;
    features.flow_packet_rate = 0.0;
    features.ack_packet_count = 0;

    // Check if data is empty
    if (flow_data.empty()) {
        return features;
    }

    // Accumulators for computing means
    double total_packet_len = 0.0;
    double total_fwd_packet_len = 0.0;
    double total_bwd_packet_len = 0.0;

    for (const auto& flow : flow_data) {
        // Update max and min packet lengths
        features.max_packet_len = std::max(features.max_packet_len, flow.features.max_packet_len);
        features.min_packet_len = std::min(features.min_packet_len, flow.features.min_packet_len);

        // Accumulate for mean calculations
        total_packet_len += flow.features.mean_packet_len;
        total_fwd_packet_len += flow.features.fwd_packet_len_mean;
        total_bwd_packet_len += flow.features.bwd_packet_len_mean;

        // Update totals
        features.total_fwd_packets += flow.features.total_fwd_packets;
        features.total_bwd_packets += flow.features.total_bwd_packets;
        features.total_fwd_bytes += flow.features.total_fwd_bytes;
        features.total_bwd_bytes += flow.features.total_bwd_bytes;

        // Accumulate flow duration and ACK packet count
        features.flow_duration += flow.features.flow_duration;
        features.ack_packet_count += flow.features.ack_packet_count;
    }

    // Compute means
    features.mean_packet_len = total_packet_len / flow_data.size();
    features.fwd_packet_len_mean = total_fwd_packet_len / flow_data.size();
    features.bwd_packet_len_mean = total_bwd_packet_len / flow_data.size();

    // Compute flow-level rates
    features.flow_byte_rate = static_cast<double>(features.total_fwd_bytes + features.total_bwd_bytes) /
                              static_cast<double>(features.flow_duration);
    features.flow_packet_rate = static_cast<double>(features.total_fwd_packets + features.total_bwd_packets) /
                                static_cast<double>(features.flow_duration);

    return features;
}
