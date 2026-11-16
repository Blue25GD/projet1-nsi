//
// Created by Alexandru Popescu on 16/11/2026.
//

#ifndef PROJET1_NSI_MENU_H
#define PROJET1_NSI_MENU_H

enum MainMenuResponse {
    QUIT = 0,
    WRITE = 1,
    READ = 2,
    INVALID
};

class Menu {
public:
    Menu() = default;
    ~Menu() = default;

    MainMenuResponse DisplayMainMenu();
};


#endif //PROJET1_NSI_MENU_H
