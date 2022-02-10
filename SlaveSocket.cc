#include <string>
#include "SlaveSocket.hh"

SlaveSocket::SlaveSocket(SocketConfig config, SocketDelegate *delegate) :
    Socket(config), m_delegate(delegate) {
}

SlaveSocket::~SlaveSocket() {
    close_server();
}

void SlaveSocket::run() {
    wait_for_connection();
    while (true) {
        m_delegate->put_in_string(receive_string());
        m_delegate->callback();
        if (m_delegate->will_reply()) send_string(m_delegate->take_out_string());
        if (m_delegate->is_finished()) break;
    }
}
