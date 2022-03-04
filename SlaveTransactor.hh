#ifndef SLAVE_TRANSACTOR_HH
#define SLAVE_TRANSACTOR_HH

#include <string>
#include "SocketServer.hh"
#include "SocketConfig.hh"
#include "TransactorDelegate.hh"
#include "Logger.hh"

class SlaveTransactor {
private:
    std::string m_name;
    SocketServer *m_server;
    TransactorDelegate *m_delegate;
    Logger &m_logger = Logger::get_logger();

public:
    SlaveTransactor(std::string name, int socket_port, TransactorDelegate *delegate) :
        m_name(name), m_delegate(delegate) {
        SocketConfig config;
        config.port = socket_port;
        m_server = new SocketServer(m_name, config);
    }

    ~SlaveTransactor() {
        m_server->close_socket();
        delete m_server;
    }

    virtual void run() {
        while (true) {
            if (!m_server->is_connected()) m_server->wait_for_connection();
            m_delegate->put_in_string(m_server->receive_string());
            m_delegate->callback();
            if (m_delegate->will_reply()) m_server->send_string(m_delegate->take_out_string());
            if (m_delegate->is_finished()) break;
        }
    }

    void turn_on_debug_mode() {
        m_logger.do_print();
    }

    void turn_off_debug_mode() {
        m_logger.do_not_print();
    }
};

#endif
