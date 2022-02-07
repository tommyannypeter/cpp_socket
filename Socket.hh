#ifndef SOCKET_HH
#define SOCKET_HH

#include <string.h>
#include <string>
#include <unistd.h>
#ifdef __linux__
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#elif _WIN32
#include <winsock.h>
#endif
#include "SocketConfig.hh"

class Socket {
private:
    struct SocketConfig m_config;
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
    bool m_is_connected = false;

public:
    Socket(SocketConfig config);
    ~Socket();

    virtual void wait_for_connection() final;
    virtual void send_string(std::string str) final;
    virtual std::string receive_string() final;
    virtual void close_server() final;

private:
    void assert_connection();
};

#endif
