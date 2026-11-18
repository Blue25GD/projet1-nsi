#pragma once
#include <filesystem>

#include "Database.hpp"

class DiskHandler {
   public:
    DiskHandler() = default;
    ~DiskHandler() = default;

    /// Writes the database to disk. Returns true if the operation was successful, false otherwise.
    static bool write(const DBStorage& db);

    static DBStorage read();

   private:
    static std::filesystem::path getFilePath() {
        return std::filesystem::path(PROJECT_ROOT_DIR) / "database.txt";
    }
};
