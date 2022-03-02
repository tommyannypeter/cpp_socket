#ifndef SOCKET_CLIENT_HH
#define SOCKET_CLIENT_HH

#include "Socket.hh"

class SocketClient : public Socket {
public:
    SocketClient(std::string name, SocketConfig config) : Socket(name, config) {}

    ~SocketClient() {
    }

    void wait_for_connection() {
        print_debug("Connecting To Server...");
        m_connection = m_socket_handle;
        connect(m_connection, (struct sockaddr *)&m_address, m_address_size);
        m_is_connected = true;
        print_debug("Connected Successfully");
    }
};

#endif
