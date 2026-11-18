#include "Database.hpp"

#include "DiskHandler.hpp"

void Database::init() { data = DiskHandler::read(); }

std::optional<Name> Database::createName(const std::string_view input) {
    std::string name;
    name.reserve(input.length());

    for (const char c : input) {
        if (!std::isalpha(c) && !std::isspace(c)) return std::nullopt;
        name += c;
    }

    return Name{std::move(name)};
}

std::optional<PhoneNumber> Database::createPhoneNumber(const std::string_view input) {
    uint64_t number = 0;

    for (const char c : input) {
        if (std::isspace(c)) continue;
        if (!std::isdigit(c)) return std::nullopt;
        number = number * 10 + (c - '0');
    }

    return PhoneNumber{number};
}

void Database::insert(Name&& name, const PhoneNumber phoneNumber) {
    data[std::move(name)] = phoneNumber;

    DiskHandler::write(data);
}

std::optional<PhoneNumber> Database::at(Name&& name) {
    auto it = data.find(name);
    if (it == data.end()) return std::nullopt;

    return it->second;
}
