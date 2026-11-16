#pragma once

#include <ankerl/unordered_dense.h>

#include <cstdint>

class Name {
    std::string name;

   public:
    explicit Name(std::string&& name) : name(std::move(name)) {}

    [[nodiscard]] const std::string& get() const { return name; }
};

class PhoneNumber {
    uint64_t number;

   public:
    explicit PhoneNumber(const uint64_t number) : number(number) {}

    [[nodiscard]] uint64_t get() const { return number; }
};

struct Database {
    ankerl::unordered_dense::map<Name, PhoneNumber>;
};

/// Returns std::nullopt if the name is invalid, or the parsed `Name` otherwise.
inline std::optional<Name> createName(const std::string_view input) {
    std::string name;
    name.reserve(input.length());

    for (const char c : input) {
        if (std::isspace(c)) continue;
        if (!std::isalpha(c)) return std::nullopt;
        name += c;
    }

    return Name{std::move(name)};
}

/// Returns std::nullopt if the phone number is invalid, or the parsed `PhoneNumber` otherwise.
inline std::optional<PhoneNumber> createPhoneNumber(const std::string_view input) {
    uint64_t number = 0;

    for (const char c : input) {
        if (std::isspace(c)) continue;
        if (!std::isdigit(c)) return std::nullopt;
        number = number * 10 + (c - '0');
    }

    return PhoneNumber{number};
}
