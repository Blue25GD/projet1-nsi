//
// Created by Alexandru Popescu on 16/11/2026.
//

#include "Menu.hpp"
#include <cstdio>
#include <iostream>
#include <string>

MainMenuResponse Menu::displayMainMenu() {
    printf("0 - Quitter\n"
        "1 - Écrire dans le répertoire\n"
        "2 - Rechercher dans le répertoire\n"
        "Votre choix ? ");

    std::string input;
    std::cin >> input;

    if (input.length() != 1) {
        return INVALID;
    }
    int in = input[0] - '0';

    if (in < 0 || in > 2) {
        return INVALID;
    }

    return static_cast<MainMenuResponse>(in);
}

void Menu::printError(const char *error) {
    printf("%s\n", error);
}

std::optional<Name> Menu::readNameFromUser(const char *prompt) {
    printf("%s", prompt);
    std::string input;
    std::cin >> input;
    auto name = createName(input);
    if (!name) {
        if (input == "0") {
            return std::nullopt;
        }
        throw std::invalid_argument("name");
    }
    return *name;
}

PhoneNumber Menu::readPhoneNumberFromUser(const char *prompt) {
    printf("%s", prompt);
    std::string input;
    std::cin >> input;
    auto number = createPhoneNumber(input);
    if (!number) {
        throw std::invalid_argument("number");
    }
    return *number;
}

void Menu::read() {
    const char *namePrompt = "Entrer un nom : ";
    auto name = readNameFromUser(namePrompt);
    if (!name) {
        throw std::invalid_argument("name");
    }
    // TODO: Read from DB
}

void Menu::write() {
    while (true) {
        const char *namePrompt = "Nom (0 pour terminer) : ";
        auto name = readNameFromUser(namePrompt);
        if (!name) {
            return;
        }

        const char *phoneNumberPrompt = "Téléphone : ";
        PhoneNumber phoneNumber = readPhoneNumberFromUser(phoneNumberPrompt);
        // TODO: Write to DB
    }
}

void Menu::show() {
    MainMenuResponse res = displayMainMenu();

    switch (res) {
        case INVALID: {
            const char *message = "Commande invalide";
            printError(message);
            break;
        }
        case QUIT:
            printf("Bye!\n");
            break;
        case WRITE:
            write();
            break;
        case READ:
            read();
            break;
    }
}
