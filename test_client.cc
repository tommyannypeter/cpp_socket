#include "SocketClient.hh"
#include "SocketConfig.hh"
#include <iostream>

int main() {
    SocketConfig config;
    config.port = 13579;

    SocketClient client("client", config);
    client.turn_on_debug_mode();
    client.wait_for_connection();
    client.send_string("Here is client.");
    std::cout << client.receive_string() << std::endl;
    client.close_socket();

    return 0;
}
