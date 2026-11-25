
#include "DBThread.hpp"

DBThread::~DBThread() { close(); }

void DBThread::init(Database& db) { this->db = &db; }

void DBThread::write() noexcept {
    dirty.store(true, std::memory_order_relaxed);
}

void DBThread::run() {
    std::unique_lock<std::mutex> lock(mutex);

    while (running) {
        if (cv.wait_for(lock, SAVE_INTERVAL,
                        [this] { return !running; })) {
            break;
                        }

        if (!dirty.exchange(false, std::memory_order_relaxed))
            continue;

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

void DBThread::start() {
    running = true;
    thread = std::thread(&DBThread::run, this);
}