#pragma once

#include <string>
#include <map>
#include <vector>

std::map<std::string, std::vector<std::string>> GRAMMAR = {
    { "MENU"  , { "id", "title", "BUTTON" } },
    { "BUTTON", { "description", "target" } }
};