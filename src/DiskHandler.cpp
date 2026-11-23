#include "DiskHandler.hpp"

#include <cassert>
#include <fstream>

bool DiskHandler::write(const DBStorage& data) {
    assert(fileStream.is_open() && "File stream is not open. Call init() before writing to disk.");

    for (const auto& [name, phone] : data) {
        fileStream << name.get() << ":" << phone.get() << "\n";
    }

    return true;
}

DBStorage DiskHandler::read() {
    DBStorage db;

    std::ifstream inputFileStream(getFilePath());
    if (!inputFileStream.is_open()) return db;  // No database stored

    std::string line;
    while (std::getline(inputFileStream, line)) {
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
