#include <algorithm>

#include "Parser.hpp"
#include "logger.hpp"
#include "GrammaticalParserException.hpp"

using namespace std;

Parser::Parser(const vector<MachinaExpression>& expressions)
    : _expressions { expressions }, 
      _currentExpressionIterator { _expressions.begin() }
{
    _status = Statuses::Parent;
}

void Parser::fetchNextExpression() {
    _currentExpressionIterator++;
}

grammarValues& Parser::checkToken(const std::string& key) {
    const auto iterator = GRAMMAR.find(key);
    if (iterator == GRAMMAR.end()) {
        throw GrammaticalParserException { "Unexpected token : " + key };
    }
    return iterator->second;
}

void Parser::parseParent() {
    checkToken(_currentExpressionKey);
    _tree.addAndMoveToChild(_currentExpressionKey, _currentExpressionKeyValues);
    _status = Statuses::OpeningBrace;
}

void Parser::parseOpeningBrace() {
    if (_currentExpressionKey != "{") {
        throw GrammaticalParserException { "Expected an opening brace at the token : " + _currentNodeKey };
    }
    _status = Statuses::Body;
}

void Parser::checkKeyIterator(grammarValues& values, const grammarValues::iterator& keyIterator) {
    if (keyIterator == values.end()) {
        throw GrammaticalParserException { "Token : " + _currentNodeKey + " has no member named " + _currentExpressionKey };
    }
    if (keyIterator->second != DEFAULT_VALUE) {
        throw GrammaticalParserException { "Token : " + _currentNodeKey + " cannot have two members: " + _currentExpressionKey };
    }
    if (GRAMMAR.contains(_currentExpressionKey)) { // it is a parent token
        _tree.addAndMoveToChild(_currentExpressionKey, _currentExpressionKeyValues);
        _status = Statuses::OpeningBrace;
    }
    else {
        _tree.addChild(_currentExpressionKey, _currentExpressionKeyValues);
    }
    keyIterator->second = "#VALUE"; // TODO : set the right value
}

void Parser::parseBody() {
    if (_currentExpressionKey == "}") {
        _status = Statuses::ClosingBrace;
    }
    else {
        grammarValues& values = checkToken(_currentNodeKey);
        auto keyIterator = find_if(values.begin(), values.end(), [this](const pair<string, string>& element){ 
            return element.first == _currentExpressionKey; 
        });
        checkKeyIterator(values, keyIterator);
    }
}

void Parser::parseClosingBrace() {
    grammarValues& values = checkToken(_currentNodeKey);

    for (pair<string, string>& value: values) { // check if the parent token has all of its token
        infos(value.first + ", " + value.second);
        if (value.second == DEFAULT_VALUE) {
            throw GrammaticalParserException { "Expected more values for the token : " + _currentNodeKey + ", missing : " + value.first };
        }
        else {
            value.second = DEFAULT_VALUE;
        }
    }

    _tree.moveToParent();
    _tree.isRoot() ? _status = Statuses::Parent : _status = Statuses::Body;
}

void Parser::validateGrammar() {
    _currentExpressionKey = _currentExpressionIterator->getKey();
    _currentExpressionKeyValues = _currentExpressionIterator->getValues();
    _currentNodeKey = _tree.getCurrentNode().getKey();

    try {
        switch (_status) {
            case Statuses::Parent:
                parseParent();
                break;
            case Statuses::OpeningBrace:
                parseOpeningBrace();
                break;
            case Statuses::Body:
                parseBody();
                break;
            case Statuses::ClosingBrace:
                parseClosingBrace();
                break;
            default:
                throw GrammaticalParserException { "Unexpected behaviour occured" };
                break;
        }
    } catch (const GrammaticalParserException& gpe) {
        throw GrammaticalParserException { "Exception caught while validating grammar on status " + Statuses::statuses_str[_status] + " with error : " + gpe.what() };
    }
}

void Parser::parse() {
    while (_currentExpressionIterator != _expressions.end()) {
        validateGrammar();
        
        if (_status == Statuses::Parent || _status == Statuses::OpeningBrace || _status == Statuses::Body) {
            fetchNextExpression();
        }
    }

    if (!_tree.isRoot()) {
        throw GrammaticalParserException { "Expected a closing brace for the token : " + _tree.getCurrentNode().getKey() };
    }
    _tree.moveToRoot();
    _tree.display(_tree.getRoot());
}