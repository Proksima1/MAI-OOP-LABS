#pragma once

#include "iostream"

class NotImplemented : public std::exception {
private:
    std::string _msg;
public:
    NotImplemented(const char *msg) {
        this->_msg = msg;
    }

    const char *what() const noexcept {
        return _msg.c_str();
    }
};