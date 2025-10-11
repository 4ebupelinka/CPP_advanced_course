#include "Task_7_students.h"
#include <iostream>
#include <string>


struct Date {
    int day;
    int month;
    int year;
};

struct Student {
    std::string fullName;
    Date birthDate;
    int grades[5];
};


void printStudent(const Student& s) {
    std::cout << "ФИО: " << s.fullName << "\n";
    std::cout << "Дата рождения: "
        << s.birthDate.day << "."
        << s.birthDate.month << "."
        << s.birthDate.year << "\n";

    std::cout << "Оценки: ";
    for (int i = 0; i < 5; ++i) {
        std::cout << s.grades[i] << " ";
    }
    std::cout << "\n";
}


double getAverageRating(const Student& s) {
    int sum = 0;
    for (int i = 0; i < 5; ++i) {
        sum += s.grades[i];
    }
    return static_cast<double>(sum) / 5.0;
}


void RunTask7() {
    Student group[] = {
        { "Тараканов Борис Александрович", {10, 6, 2003}, {5, 5, 4, 5, 5} },
        { "Жумасынба Игорь Платонович", {15, 7, 2001}, {3, 4, 3, 4, 4} },
        { "Перевозчиков Даниил Непомнюотчество", {20, 12, 2002}, {3, 3, 3, 4, 5} },
        { "Гребенщикова София Анатольевна", {28, 8, 2003}, {5, 5, 5, 5, 5} },
        { "Кочкарев Станислав Александрович", {30, 5, 2002}, {5, 4, 4, 5, 5} }
    };

    const int studentCount = sizeof(group) / sizeof(group[0]);

    std::cout << "Студенты со средним баллом выше 4.0:\n";
    for (int i = 0; i < studentCount; ++i) {
        double avg = getAverageRating(group[i]);
        if (avg > 4.0) {
            printStudent(group[i]);
            std::cout << "Средний балл: " << avg << "\n\n";
        }
    }
}
