#include <algorithm>

#include "GrammaticalParser.hpp"
#include "logger.hpp"
#include "GrammaticalParserException.hpp"
#include "vector_util.hpp"

using namespace std;

GrammaticalParser *GrammaticalParser::getInstance(const vector<MachinaExpression>& expressions) {
    if (_instance == nullptr) {
        _instance = new GrammaticalParser(expressions);
    }
    return _instance;
}

GrammaticalParser::GrammaticalParser(const vector<MachinaExpression>& expressions)
    : _expressions { expressions }, 
      _currentExpressionIterator { _expressions.begin() },
      _currentExpressionFilePosition { 0 }
{
    _status = Statuses::Parent;
}

void GrammaticalParser::fetchNextExpression() {
    _currentExpressionIterator++;
}

grammarValues GrammaticalParser::checkAndGetGrammarValuesByKey(const std::string& key) {
    auto grammarMap = grammar->get();
    const auto iterator = grammarMap.find(key);
    if (iterator == grammarMap.end()) {
        throw GrammaticalParserException { "Unexpected primary token at line " + to_string(_currentExpressionFilePosition) + " : " + key };
    }
    return grammarMap.at(iterator->first);
}

void GrammaticalParser::parseParent() {
    grammarValues valuesToCheck = checkAndGetGrammarValuesByKey(_currentExpressionKey);
    _grammarResult.emplace(valuesToCheck);
    _tree.addAndMoveToChild(_currentExpressionKey, _currentExpressionKeyValues, _currentExpressionFilePosition);
    _status = Statuses::OpeningBrace;
}

void GrammaticalParser::parseOpeningBrace() {
    if (_currentExpressionKey != "{") {
        throw GrammaticalParserException { "Expected an opening brace at line " + to_string(_currentExpressionFilePosition) + " for the token : " + _currentNodeKey };
    }
    _status = Statuses::Body;
}

void GrammaticalParser::checkKeyIterator(grammarValues& values, const grammarValues::iterator& keyIterator) {
    if (keyIterator == values.end()) {
        throw GrammaticalParserException { "Token : " + _currentNodeKey + " has no member named " + _currentExpressionKey + " at line " + to_string(_currentExpressionFilePosition) };
    }
    if (keyIterator->second != grammar->defaultValue()) {
        throw GrammaticalParserException { "Token : " + _currentNodeKey + " cannot have two members: " + _currentExpressionKey + " at line " + to_string(_currentExpressionFilePosition) };
    }
    long long index = distance(values.begin(), keyIterator);
    _grammarResult.top().at(index).second = "#VALUE";
    if (grammar->get().contains(_currentExpressionKey)) { // it is a parent token
        parseParent();
    } else {
        _tree.addChild(_currentExpressionKey, _currentExpressionKeyValues, _currentExpressionFilePosition);
    }
}

void GrammaticalParser::parseBody() {
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

void GrammaticalParser::parseClosingBrace() {
    for (pair<string, string>& value: _grammarResult.top()) { 
        // check if the parent token has all of its token
        if (value.second == grammar->defaultValue()) {
            throw GrammaticalParserException { "Expected more values for the token " + _currentNodeKey + " at line " + to_string(_tree.getCurrentNode().getFilePosition()) + ", missing : " + value.first };
        }
    }
    _grammarResult.pop();

    _tree.moveToParent();
    _tree.isRoot() ? _status = Statuses::Parent : _status = Statuses::Body;
}

void GrammaticalParser::validateGrammar() {
    _currentExpressionKey = _currentExpressionIterator->getKey();
    _currentExpressionKeyValues = _currentExpressionIterator->getValues();
    _currentExpressionFilePosition = _currentExpressionIterator->getFilePosition();
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

const Tree& GrammaticalParser::parse() {
    while (_currentExpressionIterator != _expressions.end()) {
        log("Parsing expression ...",
            "Current key : '" + _currentExpressionKey + "'",
            "Current values : '" + toString(_currentExpressionKeyValues) + "'", 
            "Status : " + to_string(_status),
            "Current Node key from tree : " + _currentNodeKey);
        validateGrammar();
        
        if (_status == Statuses::Parent || _status == Statuses::OpeningBrace || _status == Statuses::Body) {
            fetchNextExpression();
        }
    }

    if (!_tree.isRoot()) {
        throw GrammaticalParserException { "Expected a closing brace for the token : " + _tree.getCurrentNode().getKey() + " at line " + to_string(_tree.getCurrentNode().getFilePosition()) };
    }
    _tree.moveToRoot();
    _tree.display();
    return _tree;
}
