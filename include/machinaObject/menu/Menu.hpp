#pragma once

#include <string_view>

#include "Button.hpp"

class Menu {
    private:
        const int _id;
        std::string_view _title;
        Button _button;

    public:
        Menu(const int id, std::string_view title, const Button button);

        void display();

        int getId();

};
