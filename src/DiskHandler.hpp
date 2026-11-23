#pragma once
#include <filesystem>
#include <fstream>

#include "DBStorage.hpp"

class DiskHandler {
    std::ofstream fileStream;

   public:
    DiskHandler() = default;
    ~DiskHandler() = default;

    void init() { fileStream = std::ofstream(getFilePath()); }

    /// Writes the database to disk. Returns true if the operation was successful, false otherwise.
    bool write(const DBStorage& db);

    static DBStorage read();

   private:
    static std::filesystem::path getFilePath() {
        return std::filesystem::path(PROJECT_ROOT_DIR) / "database.txt";
    }
};
