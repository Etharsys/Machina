#pragma once

#include <vector>

#include "Grammar.hpp"
#include "MachinaExpression.hpp"
#include "Tree.hpp"

enum Statuses { Parent, OpeningBrace, Body, ClosingBrace };

class Parser {
    private:
        std::vector<MachinaExpression> _expressions;
        std::vector<MachinaExpression>::iterator _currentExpressionIterator;

        void fetchNextExpression();
        bool parseParent(const std::string& key, Tree& tree, Statuses& status);
        bool parseOpeningBrace(const std::string& key, const std::string& currentNodeValue, Statuses& status);
        bool parseBody(const std::string& key, Tree& tree, const std::string& currentNodeValue, Statuses& status);
        bool parseClosingBrace(const std::string& key, Tree& tree, const std::string& currentNodeValue, Statuses& status);
        bool validateGrammar(MachinaExpression& expression, Tree& tree, Statuses& status);

    public:
        Parser(const std::vector<MachinaExpression>& expressions);

        void parse();
};
