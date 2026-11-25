#include "Menu.hpp"

#include <unistd.h>

#include <cstdio>
#include <iostream>
#include <string>

#include "DiskHandler.hpp"

void Menu::print(const char *message, ...) {
    static const bool isInteractive = isatty(STDOUT_FILENO);
    if (isInteractive) {
        va_list args;
        va_start(args, message);
        vprintf(message, args);
        va_end(args);
    }
}

__attribute__((cold, noinline)) void Menu::printError(const char *error) {
    print("\033[1;31mErreur : %s\n\033[0m", error);
}

MainMenuResponse Menu::displayMainMenu() {
    print(
        "0 - Quitter\n"
        "1 - Écrire dans le répertoire\n"
        "2 - Rechercher dans le répertoire\n"
        "Votre choix ? ");

    std::string input;
    std::cin >> input;

    if (input.length() != 1) {
        return MainMenuResponse::INVALID;
    }
    int in = input[0] - '0';

    if (in < 0 || in > 2) {
        return MainMenuResponse::INVALID;
    }

    return static_cast<MainMenuResponse>(in);
}

template <size_t MAX_LENGTH>
std::string_view Menu::readInput(std::array<char, MAX_LENGTH + 2> &buf) {
    while (std::fgets(buf.data(), buf.size(), stdin)) {
        char *data = buf.data();
        size_t len = std::strlen(data);

        // Strip back
        while (len > 0 && std::isspace(static_cast<unsigned char>(data[len - 1]))) --len;
        if (len > MAX_LENGTH) [[unlikely]] {
            printError("Entree trop longue\n");
            return {};
        }

        // Strip front
        while (len > 0 && std::isspace(static_cast<unsigned char>(*data))) {
            ++data;
            --len;
        }

        if (len == 0) continue;

        return {data, len};
    }

    return {};
}

std::optional<Name> Menu::readNameFromUser(const char *prompt) {
    print("%s", prompt);

    std::array<char, Name::MAX_LENGTH + 2> buf;
    const std::string_view str = readInput<Name::MAX_LENGTH>(buf);
    if (str.empty()) [[unlikely]]
        return std::nullopt;

    std::optional<Name> name = Database::createName(str);
    if (!name) [[unlikely]] {
        if (str == "0") {
            returnToMainMenu = true;
            return std::nullopt;
        }

        printError("Nom invalide\n");
        return std::nullopt;
    }

    return std::move(*name);
}

std::optional<PhoneNumber> Menu::readPhoneNumberFromUser(const char *prompt) {
    print("%s", prompt);

    std::array<char, PhoneNumber::MAX_LENGTH + 2> buf;
    const std::string_view str = readInput<PhoneNumber::MAX_LENGTH>(buf);
    if (str.empty()) [[unlikely]]
        return std::nullopt;

    std::optional<PhoneNumber> phone = Database::createPhoneNumber(str);
    if (!phone) [[unlikely]] {
        printError("Numéro de téléphone invalide\n");
        return std::nullopt;
    }
    return *phone;
}

void Menu::read() {
    const char *namePrompt = "Entrer un nom (0 pour retourner au menu principal) : ";
    std::optional<Name> name = readNameFromUser(namePrompt);
    if (!name) return;

    const std::optional<PhoneNumber> phoneNumber = db.at(std::move(*name));
    if (!phoneNumber) {
        printError("Nom introuvable\n");
        return;
    }
    print("Téléphone : %lu\n", phoneNumber->get());
}

void Menu::write() {
    while (true) {
        const char *namePrompt = "Nom (0 pour retourner au menu principal) : ";
        auto name = readNameFromUser(namePrompt);
        if (!name) return;

        const char *phoneNumberPrompt = "Téléphone : ";
        const std::optional<PhoneNumber> phoneNumber = readPhoneNumberFromUser(phoneNumberPrompt);
        if (!phoneNumber) return;

        db.insert(std::move(*name), *phoneNumber);
    }
}

void Menu::show() {
    MainMenuResponse res = displayMainMenu();

    while (true) {
        if (returnToMainMenu) {
            returnToMainMenu = false;
            res = displayMainMenu();
        }

        switch (res) {
            case MainMenuResponse::INVALID: {
                const char *message = "Commande invalide";
                printError(message);
                returnToMainMenu = true;
                break;
            }
            case MainMenuResponse::QUIT:
                print("Bye!\n");
                db.close();
                return;
            case MainMenuResponse::WRITE:
                write();
                break;
            case MainMenuResponse::READ:
                read();
                break;
        }
    }
}
