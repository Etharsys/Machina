#include "LineReader.hpp"

using namespace std;

LineReader::LineReader(string_view line)
    : _line { trim(line) } { 
}

const string LineReader::getLine() { 
    return _line; 
}

const MachinaExpression LineReader::getMachinaExpression() { 
    return _machinaExpression; 
}

const string LineReader::trim(string_view line) {
    string lineCopy { line };
    auto is_space = [](unsigned char const c) { return isspace(c); };
    lineCopy.erase(remove_if(lineCopy.begin(), lineCopy.end(), is_space), lineCopy.end());
    return lineCopy;
}

bool LineReader::skip() {
    if (_line == "" || _line.at(0) == '#') {
        infos("Skipping line : " + _line);
        return true;
    }
    if (_line.at(0) == ':') {
        throw ReaderException("Invalid character ':'" + _line);
    }
    infos("Reading line : " + _line);
    return false;
}

const std::vector<std::string> LineReader::split(string line, string_view delimiter)
{
    vector<string> tokens;
    size_t i = 0;
    while (i != string::npos) {
        i = line.find(delimiter);
        tokens.emplace_back(line.substr(0, i));
        line.erase(0, i + delimiter.length());
    } 
    return tokens;
}

void LineReader::parse()
{
    vector<string> tokens = split(_line, ":");
    _machinaExpression.set_key(tokens.at(0));
    switch(tokens.size()) {
        case 1: 
            break;
        case 2: 
            if (tokens.at(1) == "") {
                throw ReaderException("Arguments needed");
            }
            tokens = split(tokens.at(1), ",");
            for_each(tokens.begin(), tokens.end(), [this](string& e){ _machinaExpression.add(e); });
            break;
        default: 
            throw ReaderException("Impossible situation");
            break;
    }
}