#pragma once

#include <map>

#include "Menu.hpp"

class MenuManager { 
    
    private: 
        inline static MenuManager* _instance = nullptr;
        std::map<int, Menu> _menus;
        int _activeMenu;

        MenuManager() = default;
    
    public:
        MenuManager(MenuManager &other) = delete;

        void operator=(const MenuManager &) = delete;

        static MenuManager *getInstance();
        
        bool isMenuValid(const int id);

        void modify(const int newActiveMenu);

        void display();
        
        void insert(Menu menu);

};