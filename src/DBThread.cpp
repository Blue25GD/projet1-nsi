#pragma once

#include "DBThread.hpp"

void DBThread::run(Database& db) {
    while (running) {
        if (write_db) {
            db.saveToFile();
        }
    }
}

void DBThread::close() {
    running = false;
}

void DBThread::write() {
    write_db = true;
}
