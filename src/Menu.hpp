#pragma once

#include "Database.hpp"

enum class MainMenuResponse { QUIT = 0, WRITE = 1, READ = 2, INVALID };

class Menu {
    Database db;

    std::string inputBuffer;

    bool returnToMainMenu = false;

   public:
    Menu() = default;
    ~Menu() = default;

    __attribute__((format(printf, 1, 2))) static void print(const char* message, ...);
    static void printError(const char* error);

    void init() { db.init(); }

    static MainMenuResponse displayMainMenu();

    std::optional<Name> readNameFromUser(const char* prompt);

    std::optional<PhoneNumber> readPhoneNumberFromUser(const char* prompt);

    void read();
    void write();

    void show();
};
