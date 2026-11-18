//
// Created by Alexandru Popescu on 16/11/2026.
//

#ifndef PROJET1_NSI_MENU_H
#define PROJET1_NSI_MENU_H
#include "Database.hpp"

enum class MainMenuResponse { QUIT = 0, WRITE = 1, READ = 2, INVALID };

class Menu {
    Database db;

    bool returnToMainMenu = false;

   public:
    Menu() = default;
    ~Menu() = default;

    void init() { db.init(); }

    static MainMenuResponse displayMainMenu();
    static void printError(const char* error);

    std::optional<Name> readNameFromUser(const char* prompt);
    static std::optional<PhoneNumber> readPhoneNumberFromUser(const char* prompt);

    void read();
    void write();

    void show();
};

#endif  // PROJET1_NSI_MENU_H
