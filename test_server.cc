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
        if (!server.is_connected()) server.wait_for_connection();
        std::string received_str = server.receive_string();
        if (received_str.size() != 0) server.send_string("Here is server.");
    }
    server.close_socket();

    return 0;
}
