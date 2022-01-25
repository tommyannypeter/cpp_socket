#ifndef SOCKET_BASE_HH
#define SOCKET_BASE_HH

#include <stdint.h>
#ifdef __linux__
#include <sys/socket.h>
#elif _WIN32
#include <winsock.h>
#endif

struct Socket_Config {
    char* host = "127.0.0.1";
    uint16_t port;
    int max_connection_num = 1;
};

class Socket_Base {
private:
    struct Socket_Config m_config;
    int m_server_handle;
    #ifdef __linux__
    int m_opt_value = 1;
    #elif _WIN32
    char m_opt_value = 1;
    #endif
    struct sockaddr_in m_address;
    int m_address_size = sizeof(m_address);
    int m_connection;

public:
    Socket_Base(Socket_Config config);
    ~Socket_Base();

    void wait_for_connection() final;
};

#endif
