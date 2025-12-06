#include "database_manager.h"
#include <iostream>

DatabaseManager::DatabaseManager() : db(NULL) {
}

DatabaseManager::~DatabaseManager() {
    if (db != NULL) {
        sqlite3_close(db);
        db = NULL;
    }
}

bool DatabaseManager::executeInternal(const std::string& sql) {
    char* errorMessage = NULL;
    int result = sqlite3_exec(db, sql.c_str(), NULL, NULL, &errorMessage);

    if (result != SQLITE_OK) {
        std::cerr << "SQL error: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
        return false;
    }

    return true;
}

bool DatabaseManager::initialize(const std::string& filename) {
    if (sqlite3_open(filename.c_str(), &db) != SQLITE_OK) {
        std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    // Базовые настройки оптимизации
    executeInternal("PRAGMA foreign_keys = ON;");
    executeInternal("PRAGMA journal_mode = WAL;");
    sqlite3_busy_timeout(db, 5000);

    // Создание таблиц students и grades
    const char* sqlStudents =
        "CREATE TABLE IF NOT EXISTS students ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "name TEXT NOT NULL, "
        "email TEXT UNIQUE, "
        "group_name TEXT"
        ");";

    const char* sqlGrades =
        "CREATE TABLE IF NOT EXISTS grades ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "student_id INTEGER, "
        "subject TEXT, "
        "grade INTEGER, "
        "FOREIGN KEY(student_id) REFERENCES students(id) ON DELETE CASCADE"
        ");";

    if (!executeInternal(sqlStudents)) {
        return false;
    }

    if (!executeInternal(sqlGrades)) {
        return false;
    }

    return true;
}

sqlite3* DatabaseManager::getHandle() const {
    return db;
}

bool DatabaseManager::beginTransaction() {
    return executeInternal("BEGIN TRANSACTION;");
}

bool DatabaseManager::commitTransaction() {
    return executeInternal("COMMIT;");
}

bool DatabaseManager::rollbackTransaction() {
    return executeInternal("ROLLBACK;");
}
