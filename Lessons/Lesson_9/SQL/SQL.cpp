#include <sqlite3.h>
#include <iostream>
#include <string>

// Структура для представления пользователя
struct User {
    int id;
    std::string username;
    std::string email;
    std::string createdAt;
};

// Класс для управления подключением к БД
class DatabaseManager {
private:
    sqlite3* db;

public:
    DatabaseManager() : db(nullptr) {}

    ~DatabaseManager() {
        if (db) {
            sqlite3_close(db);
        }
    }

    bool initialize(const std::string& filename) {
        if (sqlite3_open(filename.c_str(), &db) != SQLITE_OK) {
            std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
            return false;
        }

        // Включаем внешние ключи и немного оптимизации (не обязательно, но полезно)
        execute("PRAGMA foreign_keys = ON;");
        execute("PRAGMA journal_mode = WAL;");
        sqlite3_busy_timeout(db, 5000);

        // Создаём таблицу users, если её ещё нет
        const char* sql = R"(
            CREATE TABLE IF NOT EXISTS users (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                username TEXT UNIQUE NOT NULL,
                email    TEXT UNIQUE NOT NULL,
                created_at DATETIME DEFAULT CURRENT_TIMESTAMP
            );
        )";

        return execute(sql);
    }

    bool execute(const std::string& sql) {
        char* errorMessage = nullptr;
        int result = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errorMessage);

        if (result != SQLITE_OK) {
            std::cerr << "SQL error: " << errorMessage << std::endl;
            sqlite3_free(errorMessage);
            return false;
        }

        return true;
    }

    sqlite3* getHandle() const { return db; }
};

// Сервис для работы с пользователями
class UserService {
private:
    DatabaseManager& dbManager;

public:
    UserService(DatabaseManager& manager) : dbManager(manager) {}

    // Создать пользователя
    // Возвращает true при успехе, а в outUser кладёт созданного пользователя
    bool createUser(const std::string& username, const std::string& email, User& outUser) {
        const std::string sql = "INSERT INTO users (username, email) VALUES (?, ?)";
        sqlite3* db = dbManager.getHandle();

        sqlite3_stmt* stmt = nullptr;
        if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
            std::cerr << "Prepare failed: " << sqlite3_errmsg(db) << std::endl;
            return false;
        }

        sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, email.c_str(), -1, SQLITE_TRANSIENT);

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            std::cerr << "Insert failed: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_finalize(stmt);
            return false;
        }

        sqlite3_finalize(stmt);

        int userId = static_cast<int>(sqlite3_last_insert_rowid(db));
        return getUserById(userId, outUser);
    }

    // Получить пользователя по id.
    // Возвращает true, если пользователь найден, и заполняет outUser.
    bool getUserById(int id, User& outUser) {
        const std::string sql =
            "SELECT id, username, email, created_at FROM users WHERE id = ?";
        sqlite3* db = dbManager.getHandle();

        sqlite3_stmt* stmt = nullptr;
        if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
            std::cerr << "Prepare failed: " << sqlite3_errmsg(db) << std::endl;
            return false;
        }

        sqlite3_bind_int(stmt, 1, id);

        bool found = false;

        if (sqlite3_step(stmt) == SQLITE_ROW) {
            outUser.id = sqlite3_column_int(stmt, 0);
            const unsigned char* uname = sqlite3_column_text(stmt, 1);
            const unsigned char* mail = sqlite3_column_text(stmt, 2);
            const unsigned char* ctime = sqlite3_column_text(stmt, 3);

            outUser.username = uname ? reinterpret_cast<const char*>(uname) : "";
            outUser.email = mail ? reinterpret_cast<const char*>(mail) : "";
            outUser.createdAt = ctime ? reinterpret_cast<const char*>(ctime) : "";

            found = true;
        }

        sqlite3_finalize(stmt);
        return found;
    }

    // Удалить пользователя по id
    bool deleteUserById(int id) {
        const std::string sql = "DELETE FROM users WHERE id = ?";
        sqlite3* db = dbManager.getHandle();

        sqlite3_stmt* stmt = nullptr;
        if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
            std::cerr << "Prepare failed: " << sqlite3_errmsg(db) << std::endl;
            return false;
        }

        sqlite3_bind_int(stmt, 1, id);

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            std::cerr << "Delete failed: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_finalize(stmt);
            return false;
        }

        sqlite3_finalize(stmt);
        return true;
    }
};

// Простое меню для работы с пользователями
void printMenu() {
    std::cout << "\n===== User DB Menu =====\n";
    std::cout << "1 - Create user\n";
    std::cout << "2 - Get user by id\n";
    std::cout << "3 - Delete user by id\n";
    std::cout << "0 - Exit\n";
    std::cout << "Choice: ";
}

int main() {
    DatabaseManager dbManager;
    if (!dbManager.initialize("users.db")) {
        std::cerr << "Failed to initialize database" << std::endl;
        return 1;
    }

    UserService userService(dbManager);

    int choice = -1;
    while (true) {
        printMenu();
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input\n";
            continue;
        }

        if (choice == 0) {
            break;
        }

        if (choice == 1) {
            std::cin.ignore(10000, '\n'); // убрать \n после числа

            std::string username;
            std::string email;

            std::cout << "Enter username: ";
            std::getline(std::cin, username);

            std::cout << "Enter email: ";
            std::getline(std::cin, email);

            User created;
            if (userService.createUser(username, email, created)) {
                std::cout << "User created:\n";
                std::cout << "  id        = " << created.id << "\n";
                std::cout << "  username  = " << created.username << "\n";
                std::cout << "  email     = " << created.email << "\n";
                std::cout << "  createdAt = " << created.createdAt << "\n";
            }
            else {
                std::cout << "Failed to create user\n";
            }
        }
        else if (choice == 2) {
            int id;
            std::cout << "Enter user id: ";
            std::cin >> id;

            User user;
            if (userService.getUserById(id, user)) {
                std::cout << "User found:\n";
                std::cout << "  id        = " << user.id << "\n";
                std::cout << "  username  = " << user.username << "\n";
                std::cout << "  email     = " << user.email << "\n";
                std::cout << "  createdAt = " << user.createdAt << "\n";
            }
            else {
                std::cout << "User not found\n";
            }
        }
        else if (choice == 3) {
            int id;
            std::cout << "Enter user id: ";
            std::cin >> id;

            if (userService.deleteUserById(id)) {
                std::cout << "User deleted\n";
            }
            else {
                std::cout << "Failed to delete user\n";
            }
        }
        else {
            std::cout << "Unknown option\n";
        }
    }

    std::cout << "Bye!\n";
    return 0;
}
