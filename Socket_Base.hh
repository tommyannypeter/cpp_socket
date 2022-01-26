#ifndef SOCKET_BASE_HH
#define SOCKET_BASE_HH

#include <stdint.h>
#include <string>
#include <unistd.h>
#ifdef __linux__
#include <sys/socket.h>
#elif _WIN32
#include <winsock.h>
#endif

struct Socket_Config {
    std::string host = "127.0.0.1";
    uint16_t port;
    int max_connection_num = 1;
    int buffer_size = 16384;
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
    char* m_buffer;

public:
    Socket_Base(Socket_Config config);
    ~Socket_Base();

    virtual void wait_for_connection() final;
    virtual void send_string(std::string str) final;
    virtual std::string receive_string() final;
    virtual void close_server() final;
};

#endif
