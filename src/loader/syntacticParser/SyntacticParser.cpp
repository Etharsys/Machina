#include <algorithm>

#include "vector_util.hpp"

#include "SyntacticParser.hpp"
#include "SyntacticParserException.hpp"

using namespace std;

SyntacticParser::SyntacticParser(const vector<pair<int, string>>& lines)
    : _lines { lines }
    { }

const vector<string> SyntacticParser::split(string line, string_view delimiter) {
    const size_t delimiterLength = delimiter.length();
    vector<string> tokens;
    size_t i = 0;
    while (i != string::npos) {
        i = line.find(delimiter);
        tokens.emplace_back(line.substr(0, i));
        line.erase(0, i + delimiterLength);
    } 
    return tokens;
}

void SyntacticParser::parseArgument(pair<int, string> currentLine) {
    MachinaExpression expression;
    vector<string> tokens = split(currentLine.second, ":");
    expression.set_key(tokens.at(0));
    expression.set_filePosition(currentLine.first);
    switch(tokens.size()) {
        case 1:
            break;
        case 2:
            if (tokens.at(1) == "") {
                throw SyntacticParserException("Arguments needed at line " + to_string(currentLine.first));
            }
            tokens = split(tokens.at(1), ",");
            for_each(tokens.begin(), tokens.end(), [&expression](string& e){ expression.add(e); });
            break;
        default:
            throw SyntacticParserException("Unexpected behaviour occured");
            break;
    }
    log("Machina expression with key : '" + expression.getKey() + "' has been added with value : '" + toString(expression.getValues()) + "'");
    _expressions.emplace_back(expression);
}

const vector<MachinaExpression> SyntacticParser::parse() {
    for_each(_lines.begin(), _lines.end(), [this](pair<int, string>& currentLine) {
        if (currentLine.second.at(0) == ':') {
            throw SyntacticParserException("Invalid character ':' at line " + to_string(currentLine.first));
        }
        parseArgument(currentLine);
    });
    return _expressions;
}
