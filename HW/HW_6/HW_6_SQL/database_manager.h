#pragma once

#include <sqlite3.h>
#include <string>

class DatabaseManager {
private:
    sqlite3* db;

    bool executeInternal(const std::string& sql);

public:
    DatabaseManager();
    ~DatabaseManager();

    bool initialize(const std::string& filename);

    sqlite3* getHandle() const;

    bool beginTransaction();
    bool commitTransaction();
    bool rollbackTransaction();
};

