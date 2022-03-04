#ifndef SLAVE_TRANSACTOR_HH
#define SLAVE_TRANSACTOR_HH

#include <string>
#include "SocketServer.hh"
#include "SocketConfig.hh"
#include "TransactorDelegate.hh"

class SlaveTransactor {
private:
    std::string m_name;
    SocketServer *m_server;
    TransactorDelegate *m_delegate;

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
};

#endif
