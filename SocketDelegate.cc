#include "SocketDelegate.hh"

SocketDelegate::SocketDelegate() {
}

SocketDelegate::~SocketDelegate() {
}

bool SocketDelegate::will_reply() {
    return m_will_reply;
}

bool SocketDelegate::is_finished() {
    return m_is_finished;
}

void put_in_string(std::string input_string) {
    m_input_string = input_string;
}

std::string put_out_string() {
    return m_output_string;
}

void SocketDelegate::callback() {
}
