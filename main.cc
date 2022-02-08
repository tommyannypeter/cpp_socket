#include <iostream>
#include "SlaveSocket.hh"
#include "SocketConfig.hh"
#include "SocketDelegate.hh"

class MyDelegate : public SocketDelegate {
    void callback() {
        std::cout << "recv: " << m_input_string << std::endl;
        if (m_input_string.size() == 0) m_is_finished = true;
        m_output_string = "Hello";
    }
};

int main() {
    SocketConfig socket_config;
    socket_config.port = 13579;
    MyDelegate socket_delegate;
    SlaveSocket socket(socket_config, socket_delegate);
    socket.run();

    return 0;
}
