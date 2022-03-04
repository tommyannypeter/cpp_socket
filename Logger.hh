#ifndef LOGGER_HH
#define LOGGER_HH

#include <iostream>
#include <string>

class Logger {
public:
    static Logger &get_logger() {
        static Logger s_logger;
        return s_logger;
    }

private:
    bool m_do_print = false;
    // bool m_save_file = false;

public:
    void log(std::string source, std::string message) {
        std::string log = "==" + source + "== " + message;
        if (m_do_print) std::cout << log << std::endl;
    }

    void do_print() {
        m_do_print = true;
    }

    void do_not_print() {
        m_do_print = false;
    }

private:
    Logger() {
    }
};

#endif
