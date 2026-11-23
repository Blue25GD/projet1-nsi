#pragma once

#include <optional>
#include <string_view>

#include "DBStorage.hpp"
#include "DiskHandler.hpp"

class Database {
    DBStorage data;
    DiskHandler diskHandler;

   public:
    void init();
    void close();

    /// Returns std::nullopt if the name is invalid, or the parsed `Name` otherwise.
    static std::optional<Name> createName(std::string_view input);

    /// Returns std::nullopt if the phone number is invalid, or the parsed `PhoneNumber` otherwise.
    static std::optional<PhoneNumber> createPhoneNumber(std::string_view input);

    void insert(Name&& name, PhoneNumber phoneNumber);

    std::optional<PhoneNumber> at(Name&& name);
};
