#include "LineReader.hpp"

using namespace std;

string LineReader::trim(string line)
{
    auto is_space = [](unsigned char const c) { return isspace(c); };
    line.erase(remove_if(line.begin(), line.end(), is_space), line.end());
    return line;
}

bool LineReader::skip()
{
    if (_line == "" || _line.at(0) == '#')
    {
        infos("Skipping line : " + _line);
        return true;
    }
    if (_line.at(0) == ':')
    {
        throw InputException("Invalid caractere ':'" + _line);
    }
    infos("Reading line : " + _line);
    return false;
}

const std::vector<std::string> LineReader::split(string line, string delimiter)
{
    vector<string> tokens;
    size_t i = 0;
    while (i != string::npos)
    {
        i = line.find(delimiter);
        tokens.emplace_back(line.substr(0, i));
        line.erase(0, i + delimiter.length());
    } 
    return tokens;
}

void LineReader::parse()
{
    vector<string> tokens = split(_line, ":");
    _m_expr.set_key(tokens.at(0));
    switch(tokens.size())
    {
        default: 
            throw InputException("Impossible situation");
        case 1: 
            break;
        case 2: 
            if (tokens.at(1) == "") throw InputException("Arguments needed");
            tokens = split(tokens.at(1), ",");
            for (u_int i = 0; i < tokens.size(); i++)
            {
                _m_expr.add(tokens.at(i));
            }
            break;
    }
}