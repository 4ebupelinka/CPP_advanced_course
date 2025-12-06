#include <iostream>
#include <vector>
#include "database_manager.h"
#include "input_validator.h"
#include "student_repository.h"
#include "optimization.h"

// Простое меню
void printMenu() {
    std::cout << "\n===== Student DB Menu =====\n";
    std::cout << "1 - Add student\n";
    std::cout << "2 - Get student by id\n";
    std::cout << "3 - Update student\n";
    std::cout << "4 - Delete student\n";
    std::cout << "5 - Add student with grades (transaction)\n";
    std::cout << "6 - Get students by group\n";
    std::cout << "7 - Get average grade by subject\n";
    std::cout << "8 - Show top students\n";
    std::cout << "9 - Optimization: create indexes + bulk insert\n";
    std::cout << "0 - Exit\n";
    std::cout << "Choice: ";
}

int main() {
    DatabaseManager dbManager;
    if (!dbManager.initialize("students.db")) {
        std::cerr << "Failed to initialize database" << std::endl;
        return 1;
    }

    InputValidator validator;
    StudentRepository repo(dbManager.getHandle(), &validator);

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
            std::cin.ignore(10000, '\n');

            std::string name;
            std::string email;
            std::string groupName;

            std::cout << "Enter name: ";
            std::getline(std::cin, name);

            std::cout << "Enter email: ";
            std::getline(std::cin, email);

            std::cout << "Enter group name: ";
            std::getline(std::cin, groupName);

            int id = -1;
            if (repo.addStudent(name, email, groupName, id)) {
                std::cout << "Student added with id = " << id << std::endl;
            }
            else {
                std::cout << "Failed to add student\n";
            }
        }
        else if (choice == 2) {
            int id;
            std::cout << "Enter student id: ";
            std::cin >> id;

            Student s;
            if (repo.getStudent(id, s)) {
                std::cout << "Student:\n";
                std::cout << "  id    = " << s.id << "\n";
                std::cout << "  name  = " << s.name << "\n";
                std::cout << "  email = " << s.email << "\n";
                std::cout << "  group = " << s.groupName << "\n";

                std::vector<Grade> grades;
                if (repo.getGradesForStudent(id, grades)) {
                    std::cout << "  Grades:\n";
                    int i;
                    for (i = 0; i < (int)grades.size(); ++i) {
                        std::cout << "    subject = " << grades[i].subject
                            << ", grade = " << grades[i].grade << "\n";
                    }
                }
            }
            else {
                std::cout << "Student not found\n";
            }
        }
        else if (choice == 3) {
            int id;
            std::cout << "Enter student id to update: ";
            std::cin >> id;
            std::cin.ignore(10000, '\n');

            Student s;
            if (!repo.getStudent(id, s)) {
                std::cout << "Student not found\n";
                continue;
            }

            std::string name;
            std::string email;
            std::string groupName;

            std::cout << "Enter new name (current: " << s.name << "): ";
            std::getline(std::cin, name);
            if (name.empty()) {
                name = s.name;
            }

            std::cout << "Enter new email (current: " << s.email << "): ";
            std::getline(std::cin, email);
            if (email.empty()) {
                email = s.email;
            }

            std::cout << "Enter new group (current: " << s.groupName << "): ";
            std::getline(std::cin, groupName);
            if (groupName.empty()) {
                groupName = s.groupName;
            }

            s.name = name;
            s.email = email;
            s.groupName = groupName;

            if (repo.updateStudent(s)) {
                std::cout << "Student updated\n";
            }
            else {
                std::cout << "Failed to update student\n";
            }
        }
        else if (choice == 4) {
            int id;
            std::cout << "Enter student id to delete: ";
            std::cin >> id;

            if (repo.deleteStudent(id)) {
                std::cout << "Student deleted\n";
            }
            else {
                std::cout << "Failed to delete student\n";
            }
        }
        else if (choice == 5) {
            std::cin.ignore(10000, '\n');

            std::string name;
            std::string email;
            std::string groupName;

            std::cout << "Enter name: ";
            std::getline(std::cin, name);

            std::cout << "Enter email: ";
            std::getline(std::cin, email);

            std::cout << "Enter group name: ";
            std::getline(std::cin, groupName);

            std::vector<Grade> grades;
            int count;
            std::cout << "How many grades to add? ";
            std::cin >> count;
            std::cin.ignore(10000, '\n');

            int i;
            for (i = 0; i < count; ++i) {
                Grade g;
                g.id = 0;
                g.studentId = 0;

                std::cout << "Subject " << (i + 1) << ": ";
                std::getline(std::cin, g.subject);

                std::cout << "Grade " << (i + 1) << ": ";
                std::cin >> g.grade;
                std::cin.ignore(10000, '\n');

                grades.push_back(g);
            }

            int newId = -1;
            if (repo.addStudentWithGrades(name, email, groupName, grades, newId)) {
                std::cout << "Student with grades added, id = " << newId << std::endl;
            }
            else {
                std::cout << "Failed to add student with grades\n";
            }
        }
        else if (choice == 6) {
            std::cin.ignore(10000, '\n');
            std::string groupName;
            std::cout << "Enter group name: ";
            std::getline(std::cin, groupName);

            std::vector<Student> students;
            if (repo.getStudentsByGroup(groupName, students)) {
                std::cout << "Students in group " << groupName << ":\n";
                int i;
                for (i = 0; i < (int)students.size(); ++i) {
                    std::cout << "  id = " << students[i].id
                        << ", name = " << students[i].name << "\n";
                }
            }
            else {
                std::cout << "Query failed\n";
            }
        }
        else if (choice == 7) {
            std::cin.ignore(10000, '\n');
            std::string subject;
            std::cout << "Enter subject: ";
            std::getline(std::cin, subject);

            double avg = 0.0;
            bool found = false;
            if (repo.getAverageGradeBySubject(subject, avg, found)) {
                if (found) {
                    std::cout << "Average grade for " << subject << " = " << avg << std::endl;
                }
                else {
                    std::cout << "No grades found for this subject\n";
                }
            }
            else {
                std::cout << "Query failed\n";
            }
        }
        else if (choice == 8) {
            int limit;
            std::cout << "How many top students? ";
            std::cin >> limit;

            std::vector<Student> students;
            if (repo.getTopStudents(limit, students)) {
                std::cout << "Top students:\n";
                int i;
                for (i = 0; i < (int)students.size(); ++i) {
                    std::cout << "  id = " << students[i].id
                        << ", name = " << students[i].name
                        << ", email = " << students[i].email
                        << ", group = " << students[i].groupName
                        << "\n";
                }
            }
            else {
                std::cout << "Query failed\n";
            }
        }
        else if (choice == 9) {
            createIndexes(dbManager);
            bulkInsertStudents(dbManager, repo, 1000);
        }
        else {
            std::cout << "Unknown option\n";
        }
    }

    std::cout << "Bye!\n";
    return 0;
}
