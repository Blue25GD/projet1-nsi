#pragma once

#include <ankerl/unordered_dense.h>

#include <cstdint>

class Name {
    std::string name;

   public:
    explicit Name(std::string&& name) : name(std::move(name)) {}

    Name(Name&&) = default;
    Name& operator=(Name&&) = default;

    Name(const Name&) = delete;
    Name& operator=(const Name&) = delete;

    [[nodiscard]] const std::string& get() const { return name; }

    bool operator==(const Name&) const = default;
};

template <>
struct ankerl::unordered_dense::hash<Name> {
    using is_avalanching = void;
    using is_transparent = void;

    [[nodiscard]] auto operator()(const Name& n) const noexcept -> uint64_t {
        return ankerl::unordered_dense::hash<std::string_view>{}(n.get());
    }

    [[nodiscard]] auto operator()(std::string_view sv) const noexcept -> uint64_t {
        return ankerl::unordered_dense::hash<std::string_view>{}(sv);
    }
};

class PhoneNumber {
    uint64_t number;

   public:
    PhoneNumber() = default;
    explicit PhoneNumber(const uint64_t number) : number(number) {}

    PhoneNumber(PhoneNumber&&) = default;
    PhoneNumber& operator=(PhoneNumber&&) = default;

    PhoneNumber(const PhoneNumber&) = default;
    PhoneNumber& operator=(const PhoneNumber&) = default;

    [[nodiscard]] uint64_t get() const { return number; }
};

using DBStorage = ankerl::unordered_dense::map<Name, PhoneNumber>;

class Database {
    DBStorage data;

   public:
    void init();

    /// Returns std::nullopt if the name is invalid, or the parsed `Name` otherwise.
    static std::optional<Name> createName(std::string_view input);

    /// Returns std::nullopt if the phone number is invalid, or the parsed `PhoneNumber` otherwise.
    static std::optional<PhoneNumber> createPhoneNumber(std::string_view input);

    void insert(Name&& name, PhoneNumber phoneNumber);

    std::optional<PhoneNumber> at(Name&& name);
};
