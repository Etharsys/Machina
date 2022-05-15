#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>

/* here : enum of available _key (function) */
class MachinaExpression
{
    
        std::string _key;
        std::vector<std::string> _values;

    public:
        void set_key(std::string key) { _key = key; }
        const std::string get_key() { return _key; }

        void add(std::string value) { _values.emplace_back(value); }
        std::vector<std::string> get_values() { return _values; }

        friend std::ostream& operator<<(std::ostream& os, const MachinaExpression& dt);
};
