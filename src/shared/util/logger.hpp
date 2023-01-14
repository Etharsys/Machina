#pragma once

#include <iostream>
#include <string_view>
#include <ostream>
#include <stdarg.h>

#include "project_config.hpp"

#define UNPACK(...)                   \
  (void)::std::initializer_list<int>{ \
    (void((__VA_ARGS__)), 0)...       \
  }

namespace Color {

    enum Code {
        FG_RED      = 31,
        FG_GREEN    = 32,
        FG_ORANGE   = 33,
        FG_DEFAULT  = 39
    };

    class Modifier {
        Code code;

    public:

        Modifier(Code pCode) : code(pCode) {}

        friend std::ostream&
        operator<<(std::ostream& os, const Modifier& mod) {
            return os << "\033[" << mod.code << "m";
        }

    };
}

inline Color::Modifier white(Color::FG_DEFAULT);

template<class... Args>
inline void infos(std::string_view first, const Args&... args)
{
    if (MACHINA_INFOS)
    {
        Color::Modifier green(Color::FG_GREEN);
        std::cout << green << "[ INFO  ] " << first;
        UNPACK(std::cout << "\n        " << args);
        std::cout << white << std::endl;
    }
}

template<class... Args>
inline void debug(std::string_view first, const Args&... args)
{
    if (MACHINA_DEBUG)
    {
        Color::Modifier orange(Color::FG_ORANGE);
        std::cout << orange << "[ DEBUG ] " << first;
        UNPACK(std::cout << "\n        " << args);
        std::cout << white << std::endl;
    }
}

template<class... Args>
inline void error(std::string_view first, const Args&... args)
{
    if (MACHINA_ERROR)
    {
        Color::Modifier red(Color::FG_RED);
        std::cout << red << "[ ERROR ] " << first;
        UNPACK(std::cout << "\n        " << args);
        std::cout << white << std::endl;
    }
}