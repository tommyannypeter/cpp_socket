#include "SocketServer.hh"
#include "SocketConfig.hh"
#include <iostream>

int main() {
    SocketConfig config;
    config.port = 13579;

    SocketServer server("server", config);
    server.turn_on_debug_mode();
    server.wait_for_connection();
    server.send_string("Here is server.");
    std::cout << server.receive_string() << std::endl;
    server.close_socket();

    return 0;
}
