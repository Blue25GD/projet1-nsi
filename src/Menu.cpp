//
// Created by Alexandru Popescu on 16/11/2026.
//

#include "Menu.hpp"

#include <cstdio>
#include <iostream>
#include <string>

#include "DiskHandler.hpp"

MainMenuResponse Menu::displayMainMenu() {
    printf(
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

void Menu::printError(const char *error) { printf("\033[1;31mErreur : %s\n\033[0m", error); }

std::optional<Name> Menu::readNameFromUser(const char *prompt) {
    printf("%s", prompt);
    std::string input;
    std::cin >> input;
    auto name = Database::createName(input);
    if (!name) {
        if (input == "0") {
            returnToMainMenu = true;
            return std::nullopt;
        }

        printError("Nom invalide\n");
        return std::nullopt;
    }
    return std::move(*name);
}

std::optional<PhoneNumber> Menu::readPhoneNumberFromUser(const char *prompt) {
    printf("%s", prompt);
    std::string input;
    std::cin >> input;
    auto phone = Database::createPhoneNumber(input);
    if (!phone) {
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
    printf("Téléphone : %lu\n", phoneNumber->get());
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
                printf("Bye!\n");
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
