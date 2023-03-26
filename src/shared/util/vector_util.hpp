#include <string_view>
#include <vector>
#include <algorithm>

inline std::string toString(const std::vector<std::string>& v) {
    std::string s = "[";
    for_each(v.begin(), v.end(), [&s](std::string_view sv){ s = s.append(sv); });
    return s;
}