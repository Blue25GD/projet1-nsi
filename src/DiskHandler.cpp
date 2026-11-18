#include "DiskHandler.hpp"

#include <fstream>

bool DiskHandler::write(const DBStorage& data) {
    std::ofstream file(getFilePath());
    if (!file.is_open()) {
        return false;
    }

    for (const auto& [name, phone] : data) {
        file << name.get() << ":" << phone.get() << "\n";
    }

    return true;
}

DBStorage DiskHandler::read() {
    DBStorage db;
    std::ifstream file(getFilePath());
    if (!file.is_open()) {
        return db;
    }

    std::string line;
    while (std::getline(file, line)) {
        size_t pos = line.find(':');
        if (pos != std::string::npos) {
            std::string nameStr = line.substr(0, pos);
            Name name{std::move(nameStr)};

            std::string phone = line.substr(pos + 1);
            PhoneNumber phoneNumber{std::stoull(phone)};

            db[std::move(name)] = phoneNumber;
        }
    }

    return db;
}
