#pragma once

#include <exception>

#include "logger.hpp"

class InputException : public std::exception
{
    private:
        std::string _message;

    public:
        InputException()
        {
            _message = "";
        }

        InputException(const std::string& message)
        { 
            _message = message;
        }

        const char* what() const throw ()
        {
            return _message.data();
        }
};