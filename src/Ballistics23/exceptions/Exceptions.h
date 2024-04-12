//
// Created by neodima on 04.12.23.
//

#pragma once

#include <exception>
#include <string>

namespace Ballistics23::Exceptions {

class Exception : public std::exception {
private:
    std::string message_;

public:
    explicit Exception(const std::string &message) : message_(message) {}

    [[nodiscard]] const char *what() const noexcept { return message_.c_str(); }
};

void sofaErrorHandler(const int status) {
    if (status != 0) {
        throw Exception("SOFA ERROR");
    }
}
}
