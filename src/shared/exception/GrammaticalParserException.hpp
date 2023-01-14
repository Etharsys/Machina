#pragma once

#include <exception>

#include "logger.hpp"

class GrammaticalParserException : public std::exception
{
    private:
        std::string _message;

    public:
        GrammaticalParserException() {
            _message = "";
        }

        GrammaticalParserException(const std::string& message) { 
            _message = message;
        }

        const char* what() const throw () {
            return _message.data();
        }
};