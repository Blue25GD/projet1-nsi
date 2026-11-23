#pragma once

#include <thread>

#include "Database.hpp"

class DBThread {
public:
    DBThread() = default;

    ~DBThread() = default;

    void run(Database& db);
    void close();

    void write();

private:
    std::thread thread;
    std::atomic<bool> running{true};
    std::atomic<bool> write_db{false};
    Database& db;

};