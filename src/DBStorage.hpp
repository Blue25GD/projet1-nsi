#pragma once

#include <ankerl/unordered_dense.h>

class Name {
    std::string name;

   public:
    static constexpr size_t MAX_LENGTH = 30;

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
    static constexpr size_t MAX_LENGTH = 16;

    PhoneNumber() = default;
    explicit PhoneNumber(const uint64_t number) : number(number) {}

    PhoneNumber(PhoneNumber&&) = default;
    PhoneNumber& operator=(PhoneNumber&&) = default;

    PhoneNumber(const PhoneNumber&) = default;
    PhoneNumber& operator=(const PhoneNumber&) = default;

    [[nodiscard]] uint64_t get() const { return number; }
};

using DBStorage = ankerl::unordered_dense::map<Name, PhoneNumber>;
