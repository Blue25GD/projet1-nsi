#pragma once

#include "DBThread.hpp"
#include "Database.hpp"

enum class MainMenuResponse { QUIT = 0, WRITE = 1, READ = 2, INVALID };

class Menu {
    Database db;
    DBThread dbThread;

    std::string inputBuffer;

    bool returnToMainMenu = false;

   public:
    Menu() = default;
    ~Menu() = default;

    __attribute__((format(printf, 1, 2))) static void print(const char* message, ...);
    static void printError(const char* error);

    void init();

    static MainMenuResponse displayMainMenu();

    template <size_t MAX_LENGTH>
    static std::string_view readInput(std::array<char, MAX_LENGTH + 2>& buf);

    std::optional<Name> readNameFromUser(const char* prompt);

    static std::optional<PhoneNumber> readPhoneNumberFromUser(const char* prompt);

    void read();
    void write();
    void close();

    void show();
};
