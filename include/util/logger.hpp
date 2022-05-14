#pragma once

#include <iostream>
#include <string_view>
#include <stdarg.h>
#include <windows.h>

#include "project_config.hpp"

#define UNPACK(...)                   \
  (void)::std::initializer_list<int>{ \
    (void((__VA_ARGS__)), 0)...       \
  }


inline void output_color(unsigned int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

template<class... Args>
inline void infos(std::string_view first, const Args&... args)
{
    if (MACHINA_INFOS)
    {
        output_color(10);
        std::cout << "-INFOS- " << first;
        UNPACK(std::cout << "\n        " << args);
        output_color(7);
        std::cout << std::endl;
    }
}

template<class... Args>
inline void debug(std::string_view first, const Args&... args)
{
    if (MACHINA_DEBUG)
    {
        output_color(14);
        std::cout << "-DEBUG- " << first;
        UNPACK(std::cout << "\n        " << args);
        output_color(7);
        std::cout << std::endl;
    }
}

template<class... Args>
inline void error(std::string_view first, const Args&... args)
{
    if (MACHINA_ERROR)
    {
        output_color(12);
        std::cout << "-ERROR- " << first;
        UNPACK(std::cout << "\n        " << args);
        output_color(7);
        std::cout << std::endl;
    }
}