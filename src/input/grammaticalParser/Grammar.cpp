#include "Grammar.hpp"

#include <cstdarg>
#include <iostream>

using namespace std;

Grammar *Grammar::getInstance() {
    if (_instance == nullptr) {
        _instance = new Grammar{};
    }
    return _instance;
}

Grammar::Grammar() {
    for_each(callbackContainer.begin(), callbackContainer.end(), [](auto && callback){
        callback();
    });
}

const grammarType Grammar::get() {
    return _grammar;
}

void Grammar::emplaceMenu() {
    vector<pairSS> values { 
        std::make_pair("id", DEFAULT_VALUE), 
        std::make_pair("title", DEFAULT_VALUE), 
        std::make_pair("BUTTON", DEFAULT_VALUE)
    };
    _grammar.try_emplace("MENU", values);
}

void Grammar::emplaceButton() {
    vector<pairSS> values { 
        std::make_pair("description", DEFAULT_VALUE), 
        std::make_pair("target", DEFAULT_VALUE)
    };
    _grammar.try_emplace("BUTTON", values);
}

const std::string Grammar::defaultValue() {
    return DEFAULT_VALUE;
}
