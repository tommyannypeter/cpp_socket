#include "Socket_Base.hh"

Socket_Base::Socket_Base(Socket_Config config) {
    m_config = config;
    m_server_handle = socket(AF_INET, SOCK_STREAM,0);
    setsockopt(m_server_handle, SOL_SOCKET, SO_REUSEADDR, &m_opt_value, sizeof(m_opt_value));
    m_address.sin_family = AF_INET;
    m_address.sin_addr.s_addr = inet_addr(m_config.host);
    m_address.sin_port = htons(m_config.port);
    bind(m_server_handle, (struct sockaddr *)&m_address, m_address_size);
    listen(m_server_handle, m_config.max_connection_num);
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
