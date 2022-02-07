#include "SocketDelegate.hh"

SocketDelegate::SocketDelegate() {
}

SocketDelegate::~SocketDelegate() {
}

std::string SocketDelegate::callback(const std::string &received_string) {
    return received_string;
}
