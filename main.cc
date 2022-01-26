#include <iostream>
#include "Socket_Base.hh"

int main() {
    Socket_Config socket_config;
    socket_config.port = 13579;
    Socket_Base socket(socket_config);
    socket.wait_for_connection();
    socket.send_string("Hello");
    std::cout << socket.receive_string() << std::endl;
    socket.close_server();

    return 0;
}
