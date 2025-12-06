#include "optimization.h"
#include <iostream>
#include <ctime>

int getStudentCount(sqlite3* db) {
    const char* sql = "SELECT COUNT(*) FROM students;";
    sqlite3_stmt* stmt = NULL;
    int count = 0;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        std::cerr << "Prepare error: " << sqlite3_errmsg(db) << std::endl;
        return 0;
    }

    int stepResult = sqlite3_step(stmt);
    if (stepResult == SQLITE_ROW) {
        count = sqlite3_column_int(stmt, 0);
    }

    sqlite3_finalize(stmt);
    return count;
}


void createIndexes(DatabaseManager& dbManager) {
    sqlite3* db = dbManager.getHandle();
    const char* sqlIndex1 =
        "CREATE INDEX IF NOT EXISTS idx_students_email ON students(email);";
    const char* sqlIndex2 =
        "CREATE INDEX IF NOT EXISTS idx_grades_student_id ON grades(student_id);";

    char* errorMessage = NULL;

    int result = sqlite3_exec(db, sqlIndex1, NULL, NULL, &errorMessage);
    if (result != SQLITE_OK) {
        std::cerr << "Create index error: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
    }

    result = sqlite3_exec(db, sqlIndex2, NULL, NULL, &errorMessage);
    if (result != SQLITE_OK) {
        std::cerr << "Create index error: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
    }
}

void bulkInsertStudents(DatabaseManager& dbManager,
    StudentRepository& repo,
    int count) {
    std::cout << "Bulk insert " << count << " students..." << std::endl;

    sqlite3* db = dbManager.getHandle();
    char* errorMessage = NULL;

    int result = sqlite3_exec(db, "BEGIN TRANSACTION;", NULL, NULL, &errorMessage);
    if (result != SQLITE_OK) {
        std::cerr << "Begin transaction error: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
        return;
    }

    std::clock_t start = std::clock();

    int offset = getStudentCount(db);

    int i;
    int gId = 0;
    for (i = 0; i < count; ++i) {
        int index = offset + i;
        std::string name = "Student " + std::to_string(index);
        std::string email = "student" + std::to_string(index) + "@university.local";
        std::string groupName = "ZFImd-01-25";

        int studentId = -1;
        if (!repo.addStudent(name, email, groupName, studentId)) {
            std::cerr << "Failed to add student " << i << std::endl;
        }
        else {
            repo.addGrade(studentId, "Math", 80 + (i % 20), gId);
        }
    }

    std::clock_t end = std::clock();

    result = sqlite3_exec(db, "COMMIT;", NULL, NULL, &errorMessage);
    if (result != SQLITE_OK) {
        std::cerr << "Commit transaction error: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
    }

    double duration = (double)(end - start) / CLOCKS_PER_SEC;
    std::cout << "Bulk insert finished in " << duration << " seconds" << std::endl;
}
