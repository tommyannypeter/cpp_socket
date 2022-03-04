#ifndef SOCKET_CONFIG_HH
#define SOCKET_CONFIG_HH

#include <string>
#include <cstdint>

struct SocketConfig {
    std::string host = "127.0.0.1";
    uint16_t port;
    int buffer_size = 16384;
};

#endif
