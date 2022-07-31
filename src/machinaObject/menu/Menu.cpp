#include "Menu.hpp"

#include <string_view>
#include <iostream>

using namespace std;

Menu::Menu(const int id, string_view title, const Button button) 
    : _id { id }, _title { title }, _button { button } 
    { }

void Menu::display() {
    cout << "I am the menu : " << _title << endl;
    _button.display();
}

int Menu::getId() {
    return _id;
}