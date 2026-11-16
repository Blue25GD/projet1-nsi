//
// Created by Alexandru Popescu on 16/11/2026.
//

#ifndef PROJET1_NSI_MENU_H
#define PROJET1_NSI_MENU_H
#include "Database.hpp"

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

    MainMenuResponse displayMainMenu();
    void printError(const char* error);

    std::optional<Name> readNameFromUser(const char *prompt);
    PhoneNumber readPhoneNumberFromUser(const char* prompt);

    void read();
    void write();

    void show();

};


#endif //PROJET1_NSI_MENU_H
