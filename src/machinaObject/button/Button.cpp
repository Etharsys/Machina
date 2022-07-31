#include "button.hpp"

#include <string_view>
#include <iostream>

#include "MenuManager.hpp"

using namespace std;

Button::Button(string_view description, const int target) 
    : _description { description }, _target { target } 
    { }

void Button::display() {
    cout << "Button : " << _description << " (to:" << _target << ")" << endl;
}

void Button::onClick() {
    MenuManager::getInstance()->modify(_target); 
}