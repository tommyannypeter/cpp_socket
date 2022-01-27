#include "Socket_Base.hh"

Socket_Base::Socket_Base(Socket_Config config) {
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

Socket_Base::~Socket_Base() {
}

void Socket_Base::wait_for_connection() {
    m_connection = accept(
        m_server_handle, (struct sockaddr *)&m_address,
        #ifdef __linux__
        (socklen_t *)&m_address_size
        #elif _WIN32
        &m_address_size
        #endif
    );
}

void Socket_Base::send_string(std::string str) {
    char* str_c = new char[str.length() + 1];
    strcpy(str_c, str.c_str());
    send(m_connection, str_c, str.length(), 0);
}

std::string Socket_Base::receive_string() {
    read(m_connection, m_buffer, m_config.buffer_size);
    return std::string(m_buffer);
}

void Socket_Base::close_server() {
    delete[] m_buffer;
    close(m_server_handle);
}
