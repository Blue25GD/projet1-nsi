#include <iostream>

#include "Menu.hpp"

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    Menu menu;
    menu.show();
    return 0;
}
