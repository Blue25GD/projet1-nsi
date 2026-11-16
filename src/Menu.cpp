//
// Created by Alexandru Popescu on 16/11/2026.
//

#include "Menu.hpp"
#include <cstdio>
#include <iostream>
#include <string>

MainMenuResponse Menu::DisplayMainMenu() {
    printf("0 - Quitter\n"
        "1 - Écrire dans le répertoire\n"
        "2 - Rechercher dans le répertoire\n"
        "Votre choix ? ");

    std::string input;
    std::cin >> input;

    if (input.length() > 1 || input[0]) {
        return INVALID;
    }
    int in = input[0] - '0';
    if (in < 0 || in > 2) {
        return INVALID;
    }

    return static_cast<MainMenuResponse>(in);
}
