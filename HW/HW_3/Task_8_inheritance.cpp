#include <iostream>
#include <string>
using namespace std;

class Person {
protected:
    string name;
    int age;

public:
    Person(string n, int a) : name(n), age(a) {}
    virtual void display() const {
        cout << "Имя: " << name << ", Возраст: " << age << endl;
    }
};

class Employee {
protected:
    string position;
    double salary;

public:
    Employee(string pos, double sal) : position(pos), salary(sal) {}
    virtual void work() const {
        cout << "Выполняет работу как сотрудник" << endl;
    }
};

class Teacher : public Person, public Employee {
private:
    string subject;
    int experienceYears;

public:
    Teacher(string n, int a, string pos, double sal, string subj, int exp)
        : Person(n, a), Employee(pos, sal), subject(subj), experienceYears(exp) {
    }

    void display() const {
        cout << "[Учитель]" << endl;
        Person::display();
        cout << "Должность: " << position << endl;
        cout << "Зарплата: " << salary << " руб." << endl;
        cout << "Предмет: " << subject << endl;
        cout << "Стаж: " << experienceYears << " лет" << endl;
    }

    void work() const {
        cout << "Учитель " << name << " проводит урок по предмету " << subject << "." << endl;
    }

    void conductLesson() const {
        cout << name << " проводит занятие для студентов." << endl;
    }
};

class Researcher {
protected:
    string researchArea;
    int publicationsCount;

public:
    Researcher(string area, int publications)
        : researchArea(area), publicationsCount(publications) {
    }

    void conductResearch() const {
        cout << "Проводит исследования в области: " << researchArea << endl;
        cout << "Количество публикаций: " << publicationsCount << endl;
    }
};

class Professor : public Teacher, public Researcher {
public:
    Professor(string n, int a, string pos, double sal, string subj, int exp,
        string area, int publications)
        : Teacher(n, a, pos, sal, subj, exp),
        Researcher(area, publications) {
    }

    void display() const {
        cout << "[Профессор]" << endl;
        Teacher::display();
        cout << "Научная область: " << researchArea << endl;
        cout << "Публикаций: " << publicationsCount << endl;
    }

    void work() const {
        cout << "Профессор " << name << " читает лекции и проводит исследования." << endl;
    }

    void publishPaper() const {
        cout << "Профессор " << name << " публикует научную статью." << endl;
    }
};

void Task_8() {
    Teacher teacher("Иван Петров", 35, "Преподаватель", 60000.0, "Математика", 10);
    Professor professor("Анна Смирнова", 50, "Профессор", 120000.0, "Физика", 25, "Квантовая механика", 80);

    cout << "==============================" << endl;
    teacher.display();
    teacher.work();
    teacher.conductLesson();

    cout << "==============================" << endl;
    professor.display();
    professor.work();
    professor.conductResearch();
    professor.publishPaper();
}
