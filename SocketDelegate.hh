#ifndef SOCKET_DELEGATE_HH
#define SOCKET_DELEGATE_HH

#include <string>

class SocketDelegate {
private:
    bool m_will_reply = true;
    bool m_is_finished = false;
    std::string m_input_string = "NOT_APPLIED";
    std::string m_output_string = "NOT_APPLIED";

public:
    SocketDelegate();
    ~SocketDelegate();

    virtual bool will_reply();
    virtual bool is_finished();

    virtual void put_in_string(std::string input_string);
    virtual std::string put_out_string();

    virtual void callback();
};

#endif
