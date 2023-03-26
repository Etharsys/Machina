#pragma once

#include <iostream>
#include <string_view>
#include <ostream>
#include <stdarg.h>

#include "project_config.hpp"

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

/* UNPACK */

inline void unpack() {}

template<class... Args>
inline void unpack(std::string_view first, const Args&... args)
{
    std::cout << "\t  " << first << std::endl;
    unpack(args...);
}

/* LOG */

template<class... Args>
inline void log(std::string_view first, const Args&... args)
{
    if (MACHINA_INFOS)
    {
        Color::Modifier green(Color::FG_GREEN);
        std::cout << green << "[  LOG  ] " << first << std::endl;
        unpack(args...);
        std::cout << white;
    }
}

/* DEBUG */

template<class... Args>
inline void debug(std::string_view first, const Args&... args)
{
    if (MACHINA_DEBUG)
    {
        Color::Modifier orange(Color::FG_ORANGE);
        std::cout << orange << "[ DEBUG ] " << first;
        unpack(args...);
        std::cout << white << std::endl;
    }
}

/* ERROR */

template<class... Args>
inline void error(std::string_view first, const Args&... args)
{
    if (MACHINA_ERROR)
    {
        Color::Modifier red(Color::FG_RED);
        std::cout << red << "[ ERROR ] " << first;
        unpack(args...);
        std::cout << white << std::endl;
    }
}
