#include <iostream>
#include <string>
using namespace std;

class Student {
private:
    string name;
    int age;
    double averageGrade;
    int grades[5];

public:
    Student(const string& studentName, int studentAge) {
        name = studentName;
        if (studentAge >= 16 && studentAge <= 100) {
            age = studentAge;
        }
        else {
            age = 18;
        }
        for (int i = 0; i < 5; i++) {
            grades[i] = 0;
        }
        averageGrade = 0.0;
    }

    void setName(const string& newName) {
        if (newName.length() > 0) {
            name = newName;
        }
    }

    string getName() const {
        return name;
    }

    void setAge(int newAge) {
        if (newAge >= 16 && newAge <= 100) {
            age = newAge;
        }
    }

    int getAge() const {
        return age;
    }

    void setGrade(int index, int grade) {
        if (index >= 0 && index < 5 && grade >= 2 && grade <= 5) {
            grades[index] = grade;
            calculateAverage();
        }
    }

    int getGrade(int index) const {
        if (index >= 0 && index < 5) {
            return grades[index];
        }
        return 0;
    }

    void calculateAverage() {
        int sum = 0;
        for (int i = 0; i < 5; i++) {
            sum += grades[i];
        }
        averageGrade = static_cast<double>(sum) / 5.0;
    }

    double getAverageGrade() const {
        return averageGrade;
    }

    bool hasScholarship() const {
        return averageGrade >= 4.5;
    }

    void displayInfo() const {
        cout << "Имя: " << name << endl;
        cout << "Возраст: " << age << endl;
        cout << "Оценки: ";
        for (int i = 0; i < 5; i++) {
            cout << grades[i] << " ";
        }
        cout << endl;
        cout << "Средний балл: " << averageGrade << endl;
    }
};

void Task_1() {
    Student student("Иван Иванов", 20);

    student.setGrade(0, 5);
    student.setGrade(1, 4);
    student.setGrade(2, 5);
    student.setGrade(3, 3);
    student.setGrade(4, 4);

    student.displayInfo();

    if (student.hasScholarship()) {
        cout << "Студент получает стипендию" << endl;
    }
    else {
        cout << "Стипендия не назначена" << endl;
    }
}
