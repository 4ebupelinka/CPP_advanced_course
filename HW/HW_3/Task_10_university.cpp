#include <iostream>
#include <string>
#include <vector>
#include <memory>
using namespace std;

class UniversityMember {
protected:
    string name;
    string id;
    string email;

public:
    UniversityMember(string n, string i, string e) : name(n), id(i), email(e) {}
    virtual ~UniversityMember() {}

    virtual void displayInfo() const = 0;
    virtual void work() const = 0;
    virtual string getRole() const = 0;

    string getId() const {
        return id;
    }

    string getName() const {
        return name;
    }
};

class Student_10 : public UniversityMember {
private:
    string major;
    int year;
    double gpa;
    vector<string> courses;

public:
    Student_10(string n, string i, string e, string m, int y, double g)
        : UniversityMember(n, i, e), major(m), year(y), gpa(g) {
    }

    void displayInfo() const {
        cout << "[Студент]" << endl;
        cout << "Имя: " << name << endl;
        cout << "ID: " << id << endl;
        cout << "Email: " << email << endl;
        cout << "Специальность: " << major << endl;
        cout << "Курс обучения: " << year << endl;
        cout << "GPA: " << gpa << endl;
        cout << "Курсы: ";
        if (courses.empty()) {
            cout << "нет";
        }
        else {
            for (size_t i = 0; i < courses.size(); i++) {
                cout << courses[i] << " ";
            }
        }
        cout << endl;
    }

    void work() const {
        cout << name << " учится на специальности " << major << "." << endl;
    }

    string getRole() const {
        return "Студент";
    }

    void enrollCourse(const string& course) {
        courses.push_back(course);
        cout << name << " записан на курс " << course << endl;
    }

    void dropCourse(const string& course) {
        for (size_t i = 0; i < courses.size(); i++) {
            if (courses[i] == course) {
                courses.erase(courses.begin() + i);
                cout << name << " отписался от курса " << course << endl;
                return;
            }
        }
        cout << "Курс не найден у студента." << endl;
    }

    void calculateGPA() {
            gpa = 0.1;
    }
};

class Professor_10 : public UniversityMember {
private:
    string department;
    string office;
    double salary;
    vector<string> teachingCourses;

public:
    Professor_10(string n, string i, string e, string d, string o, double s)
        : UniversityMember(n, i, e), department(d), office(o), salary(s) {
    }

    void displayInfo() const {
        cout << "[Профессор]" << endl;
        cout << "Имя: " << name << endl;
        cout << "ID: " << id << endl;
        cout << "Email: " << email << endl;
        cout << "Кафедра: " << department << endl;
        cout << "Кабинет: " << office << endl;
        cout << "Зарплата: " << salary << endl;
        cout << "Курсы: ";
        if (teachingCourses.empty()) {
            cout << "нет";
        }
        else {
            for (size_t i = 0; i < teachingCourses.size(); i++) {
                cout << teachingCourses[i] << " ";
            }
        }
        cout << endl;
    }

    void work() const {
        cout << name << " преподает на кафедре " << department << "." << endl;
    }

    string getRole() const {
        return "Профессор";
    }

    void assignCourse(const string& course) {
        teachingCourses.push_back(course);
        cout << name << " назначен преподавателем курса " << course << endl;
    }

    void removeCourse(const string& course) {
        for (size_t i = 0; i < teachingCourses.size(); i++) {
            if (teachingCourses[i] == course) {
                teachingCourses.erase(teachingCourses.begin() + i);
                cout << name << " снят с преподавания курса " << course << endl;
                return;
            }
        }
        cout << "Курс не найден у профессора." << endl;
    }

    double calculateSalary() const {
        return salary + teachingCourses.size() * 1000.0;
    }
};

class Course {
private:
    string courseCode;
    string courseName;
    int credits;
    Professor_10* instructor;
    vector<Student_10*> enrolledStudents;

public:
    Course(string code, string name, int cr)
        : courseCode(code), courseName(name), credits(cr), instructor(NULL) {
    }

    void setInstructor(Professor_10* prof) {
        instructor = prof;
        prof->assignCourse(courseCode);
    }

    void addStudent(Student_10* student) {
        enrolledStudents.push_back(student);
        student->enrollCourse(courseCode);
    }

    void removeStudent(const string& studentId) {
        for (size_t i = 0; i < enrolledStudents.size(); i++) {
            if (enrolledStudents[i]->getId() == studentId) {
                enrolledStudents.erase(enrolledStudents.begin() + i);
                cout << "Студент " << studentId << " удалён из курса " << courseCode << endl;
                return;
            }
        }
        cout << "Студент с ID " << studentId << " не найден." << endl;
    }

    void displayCourseInfo() const {
        cout << "[Курс]" << endl;
        cout << "Код: " << courseCode << ", Название: " << courseName << ", Кредиты: " << credits << endl;
        if (instructor) {
            cout << "Преподаватель: " << instructor->getName() << endl;
        }
        else {
            cout << "Преподаватель не назначен." << endl;
        }
        cout << "Студенты: ";
        if (enrolledStudents.empty()) {
            cout << "нет";
        }
        else {
            for (size_t i = 0; i < enrolledStudents.size(); i++) {
                cout << enrolledStudents[i]->getName() << " ";
            }
        }
        cout << endl;
    }

    string getCode() const {
        return courseCode;
    }
};


class University {
private:
    string name;
    vector<unique_ptr<UniversityMember>> members;
    vector<unique_ptr<Course>> courses;
    static int totalUniversities;

public:
    University(string n) : name(n) {
        totalUniversities++;
    }

    ~University() {
        totalUniversities--;
    }

    void addMember(unique_ptr<UniversityMember> member) {
        members.push_back(move(member));
    }

    void addCourse(unique_ptr<Course> course) {
        courses.push_back(move(course));
    }

    Student_10* findStudentById(const string& id) {
        for (size_t i = 0; i < members.size(); i++) {
            Student_10* student = dynamic_cast<Student_10*>(members[i].get());
            if (student && student->getId() == id) {
                return student;
            }
        }
        return NULL;
    }

    Professor_10* findProfessorById(const string& id) {
        for (size_t i = 0; i < members.size(); i++) {
            Professor_10* professor = dynamic_cast<Professor_10*>(members[i].get());
            if (professor && professor->getId() == id) {
                return professor;
            }
        }
        return NULL;
    }

    Course* findCourseByCode(const string& code) {
        for (size_t i = 0; i < courses.size(); i++) {
            if (courses[i]->getCode() == code) {
                return courses[i].get();
            }
        }
        return NULL;
    }

    void displayAllMembers() const {
        cout << "=== Члены университета ===" << endl;
        for (size_t i = 0; i < members.size(); i++) {
            members[i]->displayInfo();
            cout << "------------------------------" << endl;
        }
    }

    void displayAllCourses() const {
        cout << "=== Курсы университета ===" << endl;
        for (size_t i = 0; i < courses.size(); i++) {
            courses[i]->displayCourseInfo();
            cout << "------------------------------" << endl;
        }
    }

    static int getTotalUniversities() {
        return totalUniversities;
    }
};

int University::totalUniversities = 0;


void Task_10() {
    cout << "=== Создаем университет ===" << endl;
    University rudn("Университет РУДН");

    unique_ptr<Professor_10> prof1(new Professor_10("Тараканов Б.А.", "P001", "boba@rudn.ru", "IT", "B101", 80000));
    unique_ptr<Professor_10> prof2(new Professor_10("Мазур И.М.", "P002", "william@czu.ru", "Свинопасное дело", "B102", 90000));

    Professor_10* p1 = prof1.get();
    Professor_10* p2 = prof2.get();

    rudn.addMember(move(prof1));
    rudn.addMember(move(prof2));

    unique_ptr<Student_10> s1(new Student_10("Вася", "S001", "vasya@rudn.ru", "IT", 2, 4.0));
    unique_ptr<Student_10> s2(new Student_10("Мария", "S002", "maria@rudn.ru", "Свинопасное дело", 1, 4.2));

    Student_10* st1 = s1.get();
    Student_10* st2 = s2.get();

    rudn.addMember(move(s1));
    rudn.addMember(move(s2));

    unique_ptr<Course> c1(new Course("PH101", "IT-1", 5));
    unique_ptr<Course> c2(new Course("MA201", "Свинопасное дело-2", 4));

    Course* course1 = c1.get();
    Course* course2 = c2.get();

    rudn.addCourse(move(c1));
    rudn.addCourse(move(c2));

    course1->setInstructor(p1);
    course2->setInstructor(p2);

    course1->addStudent(st1);
    course1->addStudent(st2);
    course2->addStudent(st1);

    rudn.displayAllMembers();
    rudn.displayAllCourses();

    cout << "Всего университетов: " << University::getTotalUniversities() << endl;
}
