#pragma once

#include <string>
#include <vector>

#include "logger.hpp"
#include "MachinaExpression.hpp"
#include "InputException.hpp"

class LineReader 
{
    private:
        std::string _line;
        MachinaExpression _m_expr;

        std::string trim(std::string line);

        const std::vector<std::string> split(std::string line, std::string delimiter);

    public:
        LineReader(std::string line)
            : _line { trim(line) }
        { }
        
        bool skip();

        void parse();

        std::string get_line() { return _line; }
        MachinaExpression get_m_expr() { return _m_expr; }

};