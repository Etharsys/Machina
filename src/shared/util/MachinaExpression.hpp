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
        int _filePosition;

    public:
        void set_key(std::string key) { 
            _key = key; 
        }

        void set_filePosition(const int filePosition) {
            _filePosition = filePosition;
        }

        const std::string getKey() { 
            return _key; 
        }

        int getFilePosition() {
            return _filePosition;
        }

        std::vector<std::string> getValues() { 
            return _values; 
        }

        void add(std::string value) { 
            _values.emplace_back(value); 
        }

        std::string toString() const {
            std::string s = _key + ":";
            std::for_each(_values.begin(), _values.end(), [&s](const std::string& value){ s = s.append(value + " "); });
            return s;
        }

        friend std::ostream& operator<<(std::ostream& os, const MachinaExpression& dt);
};

inline std::ostream& operator<<(std::ostream& os, const MachinaExpression& o) {
    os << o.toString();
    return os;
}