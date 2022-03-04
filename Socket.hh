#ifndef SOCKET_HH
#define SOCKET_HH

#include <iostream>
#include <string>
#include <unistd.h>
#include "assert.h"
#ifdef __linux__
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#elif _WIN32
#include <winsock2.h>
#endif
#include "SocketConfig.hh"
#include "Logger.hh"

class Socket {
private:
    std::string m_name;
    struct SocketConfig m_config;
    Logger &m_logger = Logger::get_logger();
    char* m_buffer;

protected:
    int m_socket_handle;
    int m_connection;
    bool m_is_connected = false;
    struct sockaddr_in m_address;
    int m_address_size = sizeof(m_address);
    #ifdef __linux__
    int m_opt_value = 1;
    #elif _WIN32
    char m_opt_value = 1;
    #endif

protected:
    Socket(std::string name, SocketConfig config) {
        #ifdef _WIN32
        WSAData wsaData;
        WORD version = MAKEWORD(2, 2);
        int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
        #endif
        m_name = name;
        m_config = config;
        m_socket_handle = socket(AF_INET, SOCK_STREAM, 0);
        setsockopt(m_socket_handle, SOL_SOCKET, SO_REUSEADDR, &m_opt_value, sizeof(m_opt_value));
        m_address.sin_family = AF_INET;
        m_address.sin_addr.s_addr = inet_addr(m_config.host.c_str());
        m_address.sin_port = htons(m_config.port);
        m_buffer = new char[m_config.buffer_size];
        memset(m_buffer, 0, sizeof(m_buffer));
    }

    ~Socket() {
    }

    void assert_connection() {
        assert(m_is_connected == true);
    }

    void print_debug(std::string message) {
        m_logger.log(m_name, message);
    }

public:
    virtual void wait_for_connection() {}

    void send_string(std::string str) {
        assert_connection();
        char* str_c = new char[str.length() + 1];
        strcpy(str_c, str.c_str());
        print_debug("Send String: " + str);
        send(m_connection, str_c, str.length() + 1, 0);
        delete str_c;
    }

    std::string receive_string() {
        assert_connection();
        recv(m_connection, m_buffer, m_config.buffer_size, 0);
        std::string received_string = std::string(m_buffer);
        if (received_string.size() == 0) {
            m_is_connected = false;
            print_debug("Lose Connection");
        }
        else {
            print_debug("Receive String: " + received_string);
        }
        memset(m_buffer, 0, sizeof(m_buffer));
        return received_string;
    }

    void close_socket() {
        delete[] m_buffer;
        close(m_socket_handle);
    }

    void turn_on_debug_mode() {
        m_logger.do_print();
    }

    void turn_off_debug_mode() {
        m_logger.do_not_print();
    }

    bool is_connected() {
        return m_is_connected;
    }
};

#endif
