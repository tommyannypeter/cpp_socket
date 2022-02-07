#ifndef SOCKET_DELEGATE_HH
#define SOCKET_DELEGATE_HH

#include <string>

class SocketDelegate {
public:
    SocketDelegate();
    ~SocketDelegate();

    virtual std::string callback(const std::string &received_string);
};

#endif
