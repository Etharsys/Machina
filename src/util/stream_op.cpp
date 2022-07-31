#include "MachinaExpression.hpp"

std::ostream& operator<<(std::ostream& os, const MachinaExpression& o) {
    os << o._key << ":";
    std::copy(o._values.begin(), o._values.end(), std::ostream_iterator<std::string>(os, " "));
    return os;
}