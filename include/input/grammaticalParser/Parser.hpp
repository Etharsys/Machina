#pragma once

#include <vector>

#include "Grammar.hpp"
#include "MachinaExpression.hpp"

class Parser {
    private:
        std::vector<MachinaExpression> _expressions;

        bool validateGrammar();

    public:
        Parser(const std::vector<MachinaExpression>& expressions);

        void parse();
};
