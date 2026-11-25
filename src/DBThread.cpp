
#include "DBThread.hpp"

DBThread::~DBThread() { close(); }

void DBThread::init(Database& db) { this->db = &db; }

void DBThread::write() noexcept {
    dirty.store(true, std::memory_order_relaxed);
}

void DBThread::run() {
    std::unique_lock<std::mutex> lock(mutex);

    while (running) {
        std::this_thread::sleep_for(SAVE_INTERVAL);

        if (!dirty.exchange(false, std::memory_order_relaxed)) continue;

        lock.unlock();

        db->saveToFile();

        lock.lock();
    }
}

void DBThread::close() {
    running = false;

    if (thread.joinable())
        thread.join();
}

void DBThread::start() { thread = std::thread(&DBThread::run, this); }