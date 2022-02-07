#include "Socket.hh"
#include "assert.h"

Socket::Socket(SocketConfig config) {
    m_config = config;
    m_server_handle = socket(AF_INET, SOCK_STREAM,0);
    setsockopt(m_server_handle, SOL_SOCKET, SO_REUSEADDR, &m_opt_value, sizeof(m_opt_value));
    m_address.sin_family = AF_INET;
    m_address.sin_addr.s_addr = inet_addr(m_config.host.c_str());
    m_address.sin_port = htons(m_config.port);
    bind(m_server_handle, (struct sockaddr *)&m_address, m_address_size);
    listen(m_server_handle, m_config.max_connection_num);
    m_buffer = new char[m_config.buffer_size];
    memset(m_buffer, 0, sizeof(m_buffer));
}

Socket::~Socket() {
}

void Socket::wait_for_connection() {
    m_connection = accept(
        m_server_handle, (struct sockaddr *)&m_address,
        #ifdef __linux__
        (socklen_t *)&m_address_size
        #elif _WIN32
        &m_address_size
        #endif
    );
    m_is_connected = true;
}

void Socket::send_string(std::string str) {
    assert_connection();
    char* str_c = new char[str.length() + 1];
    strcpy(str_c, str.c_str());
    send(m_connection, str_c, str.length(), 0);
}

std::string Socket::receive_string() {
    assert_connection();
    read(m_connection, m_buffer, m_config.buffer_size);
    return std::string(m_buffer);
}

void Socket::close_server() {
    assert_connection();
    delete[] m_buffer;
    close(m_server_handle);
}

void Socket::assert_connection() {
    assert(m_is_connected == true);
}
