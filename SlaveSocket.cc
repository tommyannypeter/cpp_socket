#include <string>
#include "SlaveSocket.hh"

SlaveSocket::SlaveSocket(SocketConfig config, SocketDelegate delegate) :
    Socket(config), m_delegate(delegate) {
}

SlaveSocket::~SlaveSocket() {
}

void SlaveSocket::run() {
    std::string command_string = receive_string();
    std::string ack_string = m_delegate.callback(command_string);
    send_string(ack_string);
}
