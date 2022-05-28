#pragma once

#include <string>
#include <string_view>
#include <vector>
#include <algorithm>

#include "logger.hpp"
#include "MachinaExpression.hpp"
#include "ReaderException.hpp"

class LineReader 
{
    private:
        std::string _line;
        MachinaExpression _machinaExpression;

        const std::string trim(std::string_view line);
        const std::vector<std::string> split(std::string line, std::string_view delimiter);

    public:
        LineReader(std::string_view line);
        
        bool skip();
        void parse();
        const std::string getLine();
        const MachinaExpression getMachinaExpression();
};