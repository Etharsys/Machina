#include <algorithm>

#include "Parser.hpp"
#include "logger.hpp"

using namespace std;

Parser::Parser(const vector<MachinaExpression>& expressions)
    : _expressions { expressions }, _currentExpressionIterator { _expressions.begin() }
    { }

void Parser::fetchNextExpression() {
    _currentExpressionIterator++;
}

bool Parser::parseParent(const string& key, Tree& tree, Statuses& status) {
    if (!GRAMMAR.contains(key)) {
        error("Unexpected token exception, reading", key);
        return false;
    }
    tree.addAndMoveToChild(key);
    status = OpeningBrace;
    return true;
}

bool Parser::parseOpeningBrace(const string& key, const string& currentNodeValue, Statuses& status) {
    if (key != "{") {
        error("Expected an opening brace at the token", currentNodeValue);
        return false;
    }
    status = Body;
    return true;
}

bool Parser::parseBody(const string& key, Tree& tree, const string& currentNodeValue, Statuses& status) {
    if (key == "}") {
        status = ClosingBrace;
    }
    else {
        const auto iterator = GRAMMAR.find(currentNodeValue);
        if (iterator == GRAMMAR.end()) {
            error("Unexpected token exception, reading", key);
            return false;
        }
        vector<pair<string, string>>& values = iterator->second;
        auto keyIterator = find_if(values.begin(), values.end(), [&key](const pair<string, string>& element){ return element.first == key; });
        if (keyIterator == values.end()) {
            error("Unexpected token exception\n        " + currentNodeValue + " has no member named", key);
            return false;
        }
        if (keyIterator->second != "#NONE") {
            error("Unexpected token exception\n        " + currentNodeValue + " cannot have two members: ", key);
            return false;
        }
        if (GRAMMAR.contains(key)) { // it is a parent token
            tree.addAndMoveToChild(key);
            status = OpeningBrace;
        }
        else {
            tree.addChild(key);
        }
        keyIterator->second = "#VALUE";
    }
    return true;
}

bool Parser::parseClosingBrace(const string& key, Tree& tree, const string& currentNodeValue, Statuses& status) {
    const auto iterator = GRAMMAR.find(currentNodeValue);
    if (iterator == GRAMMAR.end()) {
        error("Unexpected token exception, reading", key);
        return false;
    }
    vector<pair<string, string>>& values = iterator->second;
    for (pair<string, string>& value: values) { // check if the parent token has all of its token
        if (value.second == "#NONE") {
            error("Expected more values for the token " + currentNodeValue + "\n        Missing", value.first);
            return false;
        }
        else {
            value.second = "#NONE";
        }
    }
    tree.moveToParent();
    tree.isRoot() ? status = Parent : status = Body;
    return true;
}

bool Parser::validateGrammar(MachinaExpression& expression, Tree& tree, Statuses& status) {
    const string key = expression.getKey();
    const string currentNodeValue = tree.getCurrentNode().getValue();
    bool validateExpression = true;
    switch (status) {
        case Parent:
            validateExpression = parseParent(key, tree, status);
            break;
        case OpeningBrace:
            validateExpression = parseOpeningBrace(key, currentNodeValue, status);
            break;
        case Body:
            validateExpression = parseBody(key, tree, currentNodeValue, status);
            break;
        case ClosingBrace:
            validateExpression = parseClosingBrace(key, tree, currentNodeValue, status);
            break;
        default:
            validateExpression = false;
            break;
    }
    return validateExpression;
}

void Parser::parse() {
    Tree tree = Tree();
    Statuses status = Parent;
    bool check = true;
    while (_currentExpressionIterator != _expressions.end()) {
        check = validateGrammar(*_currentExpressionIterator, tree, status);
        if (!check) {
            break;
        }
        if (status == Parent || status == OpeningBrace || status == Body) {
            fetchNextExpression();
        }
    }
    if (check && !tree.isRoot()) {
        error("Expected a closing brace for the token", tree.getCurrentNode().getValue());
    }
    tree.moveToRoot();
    tree.display(tree.getRoot());
}