#pragma once

#include <string>

#include "Tree.hpp"
#include "Button.hpp"

struct ButtonFactory {
    
    static inline std::string _description = "description";
    static inline std::string _target = "target";

    static Button generate(Tree);

};