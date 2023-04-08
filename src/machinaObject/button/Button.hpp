#pragma once

#include <string_view>

#include "Tree.hpp"

class Button {
    private:
       std::string_view _description;
       const int _target;

    public:
        Button(std::string_view description, const int target);

        void display();

        void onClick();

};