// Task_2_academic.cpp
#include <iostream>
#include <string>
using namespace std;

class Person {
protected:
    string name;
    int age;
    string address;

public:
    Person(const string& personName, int personAge, const string& personAddress)
        : name(personName), age(personAge), address(personAddress) {
    }

    virtual void displayInfo() const {
        cout << "Имя: " << name << ", Возраст: " << age << ", Адрес: " << address << endl;
    }

    virtual ~Person() {}
};

class Student : public Person {
private:
    string studentId;
    double averageGrade;

public:
    Student(const string& personName, int personAge, const string& personAddress,
        const string& studentIdentifier, double studentAverageGrade)
        : Person(personName, personAge, personAddress) {
        studentId = studentIdentifier;
        if (studentAverageGrade >= 0.0 && studentAverageGrade <= 5.0) {
            averageGrade = studentAverageGrade;
        }
        else {
            averageGrade = 0.0;
        }
    }

    void setAverageGrade(double newAverageGrade) {
        if (newAverageGrade >= 0.0 && newAverageGrade <= 5.0) {
            averageGrade = newAverageGrade;
        }
    }

    double getAverageGrade() const {
        return averageGrade;
    }

    void displayInfo() const {
        cout << "[Студент]" << endl;
        cout << "Имя: " << name << endl;
        cout << "Возраст: " << age << endl;
        cout << "Адрес: " << address << endl;
        cout << "ID студента: " << studentId << endl;
        cout << "Средний балл: " << averageGrade << endl;
    }
};

class Professor : public Person {
private:
    string department;
    double salary;
    int yearsOfExperience;

public:
    Professor(const string& personName, int personAge, const string& personAddress,
        const string& professorDepartment, double professorSalary, int experienceYears)
        : Person(personName, personAge, personAddress) {
        department = professorDepartment;
        if (professorSalary >= 0.0) {
            salary = professorSalary;
        }
        else {
            salary = 0.0;
        }
        if (experienceYears >= 0) {
            yearsOfExperience = experienceYears;
        }
        else {
            yearsOfExperience = 0;
        }
    }

    double calculateBonus() const {
        double bonus = salary * 0.02 * static_cast<double>(yearsOfExperience);
        return bonus;
    }

    void displayInfo() const {
        cout << "[Профессор]" << endl;
        cout << "Имя: " << name << endl;
        cout << "Возраст: " << age << endl;
        cout << "Адрес: " << address << endl;
        cout << "Кафедра: " << department << endl;
        cout << "Оклад: " << salary << " руб." << endl;
        cout << "Стаж: " << yearsOfExperience << " лет" << endl;
        cout << "Надбавка: " << calculateBonus() << " руб." << endl;
    }
};

void Task_2() {
    Student student("Петр Петров", 20, "ул. Студенческая, 15", "S12345", 4.3);
    Professor professor("Доктор Иванов", 45, "ул. Академическая, 10", "Компьютерные науки", 50000, 15);

    cout << "==============================" << endl;
    student.displayInfo();
    cout << "==============================" << endl;
    professor.displayInfo();
    cout << "==============================" << endl;
}
