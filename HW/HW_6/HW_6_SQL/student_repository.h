#pragma once

#include <sqlite3.h>
#include <string>
#include <vector>
#include "input_validator.h"

struct Student {
    int id;
    std::string name;
    std::string email;
    std::string groupName;
};

struct Grade {
    int id;
    int studentId;
    std::string subject;
    int grade;
};

class StudentRepository {
private:
    sqlite3* db;
    InputValidator* validator;

public:
    StudentRepository(sqlite3* dbHandle, InputValidator* inputValidator);

    // CRUD для студентов
    bool addStudent(const std::string& name,
        const std::string& email,
        const std::string& groupName,
        int& outId);

    bool getStudent(int id, Student& outStudent);
    bool updateStudent(const Student& student);
    bool deleteStudent(int id);

    // CRUD для оценок
    bool addGrade(int studentId, const std::string& subject, int grade, int& outId);
    bool getGradesForStudent(int studentId, std::vector<Grade>& outGrades);

    // Задание 3: транзакции и сложные запросы
    bool addStudentWithGrades(const std::string& name,
        const std::string& email,
        const std::string& groupName,
        const std::vector<Grade>& grades,
        int& outStudentId);

    bool getStudentsByGroup(const std::string& groupName, std::vector<Student>& outStudents);

    bool getAverageGradeBySubject(const std::string& subject, double& outAverage, bool& found);

    bool getTopStudents(int limit, std::vector<Student>& outStudents);
};

