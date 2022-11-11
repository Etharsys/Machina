#pragma once

#include <exception>

#include "logger.hpp"

class SyntacticParserException : public std::exception
{
    private:
        std::string _message;

    public:
        SyntacticParserException() {
            _message = "";
        }

        SyntacticParserException(const std::string& message) { 
            _message = message;
        }

        const char* what() const throw () {
            return _message.data();
        }
};