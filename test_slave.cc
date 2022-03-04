#include "SlaveTransactor.hh"
#include "TransactorDelegate.hh"
#include "SocketConfig.hh"
#include <iostream>

class TestDelegate : public TransactorDelegate {
public:
    TestDelegate() : TransactorDelegate() {}

    void callback() {
        if (m_input_string.size() == 0) m_will_reply = false;
    }
};

int main() {
    TestDelegate delegate;
    SlaveTransactor transactor("xtor", 13579, &delegate);
    transactor.turn_on_debug_mode();
    transactor.run();

    return 0;
}
