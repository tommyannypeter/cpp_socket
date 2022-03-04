#ifndef TRANSACTOR_DELEGATE_HH
#define TRANSACTOR_DELEGATE_HH

#include <string>

class TransactorDelegate {
protected:
    bool m_will_reply = true;
    bool m_is_finished = false;
    std::string m_input_string = "NOT_APPLIED";
    std::string m_output_string = "NOT_APPLIED";

public:
    TransactorDelegate() {}

    ~TransactorDelegate() {}

    virtual bool will_reply() {
        return m_will_reply;
    }

    virtual bool is_finished() {
        return m_is_finished;
    }

    virtual void put_in_string(std::string input_string) {
        m_input_string = input_string;
    }

    virtual std::string take_out_string() {
        return m_output_string;
    }

    virtual void callback() {}
};

#endif
