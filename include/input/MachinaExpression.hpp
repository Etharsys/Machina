#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>

class MachinaExpression
{
    private:
        std::string _key;
        std::vector<std::string> _values;

    public:
        void set_key(std::string key) { 
            _key = key; 
        }

        const std::string getKey() { 
            return _key; 
        }

        std::vector<std::string> getValues() { 
            return _values; 
        }

        void add(std::string value) { 
            _values.emplace_back(value); 
        }

        friend std::ostream& operator<<(std::ostream& os, const MachinaExpression& dt);
};
