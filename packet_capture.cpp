// packet_capture.cpp

#include <pcap.h>
#include <iostream>
#include "packet_capture.h"
// Callback function for packet processing
void packet_handler(u_char *args, const struct pcap_pkthdr *header, const u_char *packet) {
    // Extract 5-tuple information from the packet (source/destination IP, ports, etc.)
    // This is where you'll parse the packet and store flow-related data
    std::cout << "Packet captured!" << std::endl;
}

void capture_packets(const char* device) {
    char error_buffer[PCAP_ERRBUF_SIZE];
    pcap_t *handle = pcap_open_live(device, BUFSIZ, 1, 1000, error_buffer);
    
    if (handle == NULL) {
        std::cerr << "Error opening device: " << error_buffer << std::endl;
        return;
    }

    pcap_loop(handle, 0, packet_handler, NULL);
    pcap_close(handle);
}