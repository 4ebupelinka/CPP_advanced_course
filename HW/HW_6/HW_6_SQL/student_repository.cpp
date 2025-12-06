#include "student_repository.h"
#include <iostream>

StudentRepository::StudentRepository(sqlite3* dbHandle, InputValidator* inputValidator)
    : db(dbHandle), validator(inputValidator) {
}

// Вспомогательная функция для вывода ошибок
static void printSqlError(sqlite3* db, const char* stage) {
    std::cerr << stage << " error: " << sqlite3_errmsg(db) << std::endl;
}

// ---------- CRUD для студентов ----------

bool StudentRepository::addStudent(const std::string& name,
    const std::string& email,
    const std::string& groupName,
    int& outId) {
    if (validator != NULL) {
        if (!validator->isValidName(name)) {
            std::cerr << "Invalid name" << std::endl;
            return false;
        }
        if (!validator->isValidEmail(email)) {
            std::cerr << "Invalid email" << std::endl;
            return false;
        }
        if (!validator->isValidGroupName(groupName)) {
            std::cerr << "Invalid group name pattern ([A-Z]{3}md-[0-9]+-[0-9])" << std::endl;
            return false;
        }
    }

    const std::string sql =
        "INSERT INTO students (name, email, group_name) VALUES (?, ?, ?);";

    sqlite3_stmt* stmt = NULL;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL) != SQLITE_OK) {
        printSqlError(db, "Prepare");
        return false;
    }

    sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, email.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, groupName.c_str(), -1, SQLITE_TRANSIENT);

    int stepResult = sqlite3_step(stmt);
    if (stepResult != SQLITE_DONE) {
        printSqlError(db, "Insert student");
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);
    outId = (int)sqlite3_last_insert_rowid(db);
    return true;
}

bool StudentRepository::getStudent(int id, Student& outStudent) {
    const std::string sql =
        "SELECT id, name, email, group_name FROM students WHERE id = ?;";

    sqlite3_stmt* stmt = NULL;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL) != SQLITE_OK) {
        printSqlError(db, "Prepare");
        return false;
    }

    sqlite3_bind_int(stmt, 1, id);

    int stepResult = sqlite3_step(stmt);
    if (stepResult == SQLITE_ROW) {
        outStudent.id = sqlite3_column_int(stmt, 0);

        const unsigned char* nameText = sqlite3_column_text(stmt, 1);
        const unsigned char* emailText = sqlite3_column_text(stmt, 2);
        const unsigned char* groupText = sqlite3_column_text(stmt, 3);

        outStudent.name = nameText != NULL ? (const char*)nameText : "";
        outStudent.email = emailText != NULL ? (const char*)emailText : "";
        outStudent.groupName = groupText != NULL ? (const char*)groupText : "";

        sqlite3_finalize(stmt);
        return true;
    }

    sqlite3_finalize(stmt);
    return false;
}

bool StudentRepository::updateStudent(const Student& student) {
    if (validator != NULL) {
        if (!validator->isValidName(student.name)) {
            std::cerr << "Invalid name" << std::endl;
            return false;
        }
        if (!validator->isValidEmail(student.email)) {
            std::cerr << "Invalid email" << std::endl;
            return false;
        }
        if (!validator->isValidGroupName(student.groupName)) {
            std::cerr << "Invalid group name" << std::endl;
            return false;
        }
    }

    const std::string sql =
        "UPDATE students SET name = ?, email = ?, group_name = ? WHERE id = ?;";

    sqlite3_stmt* stmt = NULL;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL) != SQLITE_OK) {
        printSqlError(db, "Prepare");
        return false;
    }

    sqlite3_bind_text(stmt, 1, student.name.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, student.email.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, student.groupName.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 4, student.id);

    int stepResult = sqlite3_step(stmt);
    if (stepResult != SQLITE_DONE) {
        printSqlError(db, "Update student");
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);
    return true;
}

bool StudentRepository::deleteStudent(int id) {
    const std::string sql =
        "DELETE FROM students WHERE id = ?;";

    sqlite3_stmt* stmt = NULL;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL) != SQLITE_OK) {
        printSqlError(db, "Prepare");
        return false;
    }

    sqlite3_bind_int(stmt, 1, id);

    int stepResult = sqlite3_step(stmt);
    if (stepResult != SQLITE_DONE) {
        printSqlError(db, "Delete student");
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);
    return true;
}

// ---------- CRUD для оценок ----------

bool StudentRepository::addGrade(int studentId,
    const std::string& subject,
    int grade,
    int& outId) {
    if (validator != NULL) {
        if (!validator->isValidSubject(subject)) {
            std::cerr << "Invalid subject" << std::endl;
            return false;
        }
        if (!validator->isValidGrade(grade)) {
            std::cerr << "Invalid grade" << std::endl;
            return false;
        }
    }

    const std::string sql =
        "INSERT INTO grades (student_id, subject, grade) VALUES (?, ?, ?);";

    sqlite3_stmt* stmt = NULL;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL) != SQLITE_OK) {
        printSqlError(db, "Prepare");
        return false;
    }

    sqlite3_bind_int(stmt, 1, studentId);
    sqlite3_bind_text(stmt, 2, subject.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 3, grade);

    int stepResult = sqlite3_step(stmt);
    if (stepResult != SQLITE_DONE) {
        printSqlError(db, "Insert grade");
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);
    outId = (int)sqlite3_last_insert_rowid(db);
    return true;
}

bool StudentRepository::getGradesForStudent(int studentId, std::vector<Grade>& outGrades) {
    const std::string sql =
        "SELECT id, student_id, subject, grade FROM grades WHERE student_id = ?;";

    sqlite3_stmt* stmt = NULL;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL) != SQLITE_OK) {
        printSqlError(db, "Prepare");
        return false;
    }

    sqlite3_bind_int(stmt, 1, studentId);

    outGrades.clear();

    int stepResult = sqlite3_step(stmt);
    while (stepResult == SQLITE_ROW) {
        Grade g;
        g.id = sqlite3_column_int(stmt, 0);
        g.studentId = sqlite3_column_int(stmt, 1);

        const unsigned char* subjectText = sqlite3_column_text(stmt, 2);
        g.subject = subjectText != NULL ? (const char*)subjectText : "";

        g.grade = sqlite3_column_int(stmt, 3);

        outGrades.push_back(g);

        stepResult = sqlite3_step(stmt);
    }

    sqlite3_finalize(stmt);
    return true;
}

// ---------- Задание 3: транзакции и сложные запросы ----------

bool StudentRepository::addStudentWithGrades(const std::string& name,
    const std::string& email,
    const std::string& groupName,
    const std::vector<Grade>& grades,
    int& outStudentId) {
    char* errorMessage = NULL;
    int result = sqlite3_exec(db, "BEGIN TRANSACTION;", NULL, NULL, &errorMessage);
    if (result != SQLITE_OK) {
        std::cerr << "Begin transaction error: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
        return false;
    }

    bool success = false;
    int studentId = -1;

    if (!addStudent(name, email, groupName, studentId)) {
        success = false;
    }
    else {
        success = true;
        int i;
        for (i = 0; i < (int)grades.size(); ++i) {
            int gradeId = 0;
            if (!addGrade(studentId, grades[i].subject, grades[i].grade, gradeId)) {
                success = false;
                break;
            }
        }
    }

    if (!success) {
        result = sqlite3_exec(db, "ROLLBACK;", NULL, NULL, &errorMessage);
        if (result != SQLITE_OK) {
            std::cerr << "Rollback error: " << errorMessage << std::endl;
            sqlite3_free(errorMessage);
        }
        return false;
    }

    result = sqlite3_exec(db, "COMMIT;", NULL, NULL, &errorMessage);
    if (result != SQLITE_OK) {
        std::cerr << "Commit error: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
        return false;
    }

    outStudentId = studentId;
    return true;
}

bool StudentRepository::getStudentsByGroup(const std::string& groupName,
    std::vector<Student>& outStudents) {
    const std::string sql =
        "SELECT id, name, email, group_name FROM students WHERE group_name = ?;";

    sqlite3_stmt* stmt = NULL;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL) != SQLITE_OK) {
        printSqlError(db, "Prepare");
        return false;
    }

    sqlite3_bind_text(stmt, 1, groupName.c_str(), -1, SQLITE_TRANSIENT);

    outStudents.clear();

    int stepResult = sqlite3_step(stmt);
    while (stepResult == SQLITE_ROW) {
        Student s;
        s.id = sqlite3_column_int(stmt, 0);

        const unsigned char* nameText = sqlite3_column_text(stmt, 1);
        const unsigned char* emailText = sqlite3_column_text(stmt, 2);
        const unsigned char* groupText = sqlite3_column_text(stmt, 3);

        s.name = nameText != NULL ? (const char*)nameText : "";
        s.email = emailText != NULL ? (const char*)emailText : "";
        s.groupName = groupText != NULL ? (const char*)groupText : "";

        outStudents.push_back(s);

        stepResult = sqlite3_step(stmt);
    }

    sqlite3_finalize(stmt);
    return true;
}

bool StudentRepository::getAverageGradeBySubject(const std::string& subject,
    double& outAverage,
    bool& found) {
    const std::string sql =
        "SELECT AVG(grade) FROM grades WHERE subject = ?;";

    sqlite3_stmt* stmt = NULL;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL) != SQLITE_OK) {
        printSqlError(db, "Prepare");
        return false;
    }

    sqlite3_bind_text(stmt, 1, subject.c_str(), -1, SQLITE_TRANSIENT);

    int stepResult = sqlite3_step(stmt);
    if (stepResult == SQLITE_ROW) {
        if (sqlite3_column_type(stmt, 0) == SQLITE_NULL) {
            found = false;
        }
        else {
            outAverage = sqlite3_column_double(stmt, 0);
            found = true;
        }
    }
    else {
        found = false;
    }

    sqlite3_finalize(stmt);
    return true;
}

bool StudentRepository::getTopStudents(int limit, std::vector<Student>& outStudents) {
    const std::string sql =
        "SELECT s.id, s.name, s.email, s.group_name, AVG(g.grade) AS avg_grade "
        "FROM students s "
        "JOIN grades g ON s.id = g.student_id "
        "GROUP BY s.id, s.name, s.email, s.group_name "
        "ORDER BY avg_grade DESC "
        "LIMIT ?;";

    sqlite3_stmt* stmt = NULL;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL) != SQLITE_OK) {
        printSqlError(db, "Prepare");
        return false;
    }

    sqlite3_bind_int(stmt, 1, limit);

    outStudents.clear();

    int stepResult = sqlite3_step(stmt);
    while (stepResult == SQLITE_ROW) {
        Student s;
        s.id = sqlite3_column_int(stmt, 0);

        const unsigned char* nameText = sqlite3_column_text(stmt, 1);
        const unsigned char* emailText = sqlite3_column_text(stmt, 2);
        const unsigned char* groupText = sqlite3_column_text(stmt, 3);

        s.name = nameText != NULL ? (const char*)nameText : "";
        s.email = emailText != NULL ? (const char*)emailText : "";
        s.groupName = groupText != NULL ? (const char*)groupText : "";

        outStudents.push_back(s);

        stepResult = sqlite3_step(stmt);
    }

    sqlite3_finalize(stmt);
    return true;
}
