#include "SocketServer.hh"
#include "SocketConfig.hh"
#include <iostream>

int main() {
    SocketConfig config;
    config.port = 13579;

    SocketServer server("server", config);
    server.turn_on_debug_mode();
    server.wait_for_connection();
    while (true) {
        std::cout << server.receive_string() << std::endl;
        server.send_string("Here is server.");
    }
    server.close_socket();

    return 0;
}
