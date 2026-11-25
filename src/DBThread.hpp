
#pragma once

#include <atomic>
#include <chrono>
#include <condition_variable>
#include <mutex>
#include <thread>

#include "Database.hpp"

class DBThread {
public:
    DBThread() = default;
    ~DBThread();

    DBThread(const DBThread&) = delete;
    DBThread& operator=(const DBThread&) = delete;

    void init(Database& db);

    void write() noexcept;
    void close();

    void start();

private:
    void run();

    Database* db = nullptr;
    std::thread thread;

    std::mutex mutex;
    std::condition_variable cv;

    std::atomic<bool> dirty{false};
    std::atomic<bool> running{false};

    static constexpr auto SAVE_INTERVAL =
        std::chrono::milliseconds(100);
};
