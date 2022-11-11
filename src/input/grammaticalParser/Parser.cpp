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

grammarValues Parser::checkAndGetGrammarValuesByKey(const std::string& key) {
    auto grammarMap = grammar->get();
    const auto iterator = grammarMap.find(key);
    if (iterator == grammarMap.end()) {
        throw GrammaticalParserException { "Unexpected primary token : " + key };
    }
    return grammarMap.at(iterator->first);
}

void Parser::parseParent() {
    grammarValues valuesToCheck = checkAndGetGrammarValuesByKey(_currentExpressionKey);
    _grammarResult.emplace(valuesToCheck);
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
    if (keyIterator->second != grammar->defaultValue()) {
        throw GrammaticalParserException { "Token : " + _currentNodeKey + " cannot have two members: " + _currentExpressionKey };
    }
    int index = distance(values.begin(), keyIterator);
    _grammarResult.top().at(index).second = "#VALUE";
    if (grammar->get().contains(_currentExpressionKey)) { // it is a parent token
        parseParent();
    } else {
        _tree.addChild(_currentExpressionKey, _currentExpressionKeyValues);
    }
}

void Parser::parseBody() {
    if (_currentExpressionKey == "}") {
        _status = Statuses::ClosingBrace;
    }
    else {
        grammarValues values = _grammarResult.top();
        auto keyIterator = find_if(values.begin(), values.end(), [this](const pair<string, string>& element){ 
            return element.first == _currentExpressionKey; 
        });
        checkKeyIterator(values, keyIterator);
    }
}

void Parser::parseClosingBrace() {
    for (pair<string, string>& value: _grammarResult.top()) { 
        // check if the parent token has all of its token
        if (value.second == grammar->defaultValue()) {
            throw GrammaticalParserException { "Expected more values for the token : " + _currentNodeKey + ", missing : " + value.first };
        }
    }
    _grammarResult.pop();

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