#include "SlaveTransactor.hh"
#include "TransactorDelegate.hh"
#include "SocketConfig.hh"
#include <iostream>

int main() {
    TransactorDelegate delegate;
    SlaveTransactor transactor("xtor", 13579, &delegate);
    transactor.run();

    return 0;
}
