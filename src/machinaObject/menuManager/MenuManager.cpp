#include "MenuManager.hpp"
#include "logger.hpp"

MenuManager *MenuManager::getInstance() {
    if (_instance == nullptr) {
        _instance = new MenuManager{};
    }
    return _instance;
}

bool MenuManager::isMenuValid(const int id) {
    return _menus.find(id) != _menus.end();
}

void MenuManager::modify(const int newActiveMenu) {
    if (isMenuValid(newActiveMenu)) {
        _activeMenu = newActiveMenu;
    }
}

void MenuManager::display() {
    isMenuValid(_activeMenu) ? _menus.at(_activeMenu).display() : error("MENU NOT FOUND");
}

void MenuManager::insert(Menu menu) {
    if (isMenuValid(menu.getId())) {
        error("MENU ALREADY EXIST");
        return;
    }
    _menus.emplace(menu.getId(), menu);
}