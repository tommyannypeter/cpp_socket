#ifndef SLAVE_SOCKET_HH
#define SLAVE_SOCKET_HH

#include "Socket.hh"
#include "SocketDelegate.hh"

class SlaveSocket : private Socket {
private:
    SocketDelegate *m_delegate;

public:
    SlaveSocket(SocketConfig config, SocketDelegate *delegate);
    ~SlaveSocket();

    virtual void run();
};

#endif
