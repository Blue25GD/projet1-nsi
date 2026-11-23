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
bool Menu::readInput(char *buf) {
    static constexpr auto fmt = [] {
        std::array<char, 16> buf{'%'};
        auto [ptr, _] = std::to_chars(buf.data() + 1, buf.data() + buf.size() - 2, MAX_LENGTH);
        *ptr = 's';
        return buf;
    }();

    int res;
    while ((res = std::scanf(fmt.data(), buf) != 1)) {
        if (res == EOF) [[unlikely]] {
            return false;
        }
    }
    return true;
}

std::optional<Name> Menu::readNameFromUser(const char *prompt) {
    print("%s", prompt);

    char buf[Name::MAX_LENGTH + 1];
    if (!readInput<Name::MAX_LENGTH>(buf)) [[unlikely]]
        return std::nullopt;

    auto name = Database::createName(buf);
    if (!name) [[unlikely]] {
        if (buf[0] == '0' && buf[1] == '\0') {
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

    char buf[PhoneNumber::MAX_LENGTH + 1];
    if (!readInput<PhoneNumber::MAX_LENGTH>(buf)) [[unlikely]]
        return std::nullopt;

    auto phone = Database::createPhoneNumber(buf);
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
