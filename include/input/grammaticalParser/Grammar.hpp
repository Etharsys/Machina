#pragma once

#include <string>
#include <map>
#include <vector>
#include <utility>

const std::string DEFAULT_VALUE = "#NONE";

inline std::map<std::string, std::vector<std::pair<std::string, std::string>>> GRAMMAR = {
    { "MENU"  , { std::make_pair("id", DEFAULT_VALUE), std::make_pair("title", DEFAULT_VALUE), std::make_pair("BUTTON", DEFAULT_VALUE) } },
    { "BUTTON", { std::make_pair("description", DEFAULT_VALUE), std::make_pair("target", DEFAULT_VALUE) } }
};