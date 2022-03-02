#ifndef SOCKET_SERVER_HH
#define SOCKET_SERVER_HH

#include "Socket.hh"

class SocketServer : public Socket {
public:
    SocketServer(std::string name, SocketConfig config) : Socket(name, config) {
        bind(m_socket_handle, (struct sockaddr *)&m_address, m_address_size);
        listen(m_socket_handle, 1);
    }

    ~SocketServer() {
    }

    void wait_for_connection() {
        print_debug("Wait For Client...");
        m_connection = accept(
            m_socket_handle, (struct sockaddr *)&m_address,
            #ifdef __linux__
            (socklen_t *)&m_address_size
            #elif _WIN32
            &m_address_size
            #endif
        );
        m_is_connected = true;
        print_debug("Client Connected");
    }
};

#endif
