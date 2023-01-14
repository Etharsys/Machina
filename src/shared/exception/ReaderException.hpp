#pragma once

#include <exception>

#include "logger.hpp"

class ReaderException : public std::exception
{
    private:
        std::string _message;

    public:
        ReaderException() {
            _message = "";
        }

        ReaderException(const std::string& message) { 
            _message = message;
        }

        const char* what() const throw () {
            return _message.data();
        }
};