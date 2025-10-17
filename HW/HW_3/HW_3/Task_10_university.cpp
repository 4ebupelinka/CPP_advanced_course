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

class Student : public UniversityMember {
private:
    string major;
    int year;
    double gpa;
    vector<string> courses;

public:
    Student(string n, string i, string e, string m, int y, double g)
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
        if (!courses.empty()) {
            gpa = 4.0 - 0.1 * (5 - static_cast<int>(courses.size()));
        }
    }
};

class Professor : public UniversityMember {
private:
    string department;
    string office;
    double salary;
    vector<string> teachingCourses;

public:
    Professor(string n, string i, string e, string d, string o, double s)
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
    Professor* instructor;
    vector<Student*> enrolledStudents;

public:
    Course(string code, string name, int cr)
        : courseCode(code), courseName(name), credits(cr), instructor(NULL) {
    }

    void setInstructor(Professor* prof) {
        instructor = prof;
        prof->assignCourse(courseCode);
    }

    void addStudent(Student* student) {
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

    Student* findStudentById(const string& id) {
        for (size_t i = 0; i < members.size(); i++) {
            Student* student = dynamic_cast<Student*>(members[i].get());
            if (student && student->getId() == id) {
                return student;
            }
        }
        return NULL;
    }

    Professor* findProfessorById(const string& id) {
        for (size_t i = 0; i < members.size(); i++) {
            Professor* professor = dynamic_cast<Professor*>(members[i].get());
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
    University uni("Рудненский университет");

    unique_ptr<Professor> prof1(new Professor("Иванов И.И.", "P001", "ivanov@uni.ru", "Физика", "B101", 80000));
    unique_ptr<Professor> prof2(new Professor("Смирнов С.С.", "P002", "smirnov@uni.ru", "Математика", "B102", 90000));

    Professor* p1 = prof1.get();
    Professor* p2 = prof2.get();

    uni.addMember(move(prof1));
    uni.addMember(move(prof2));

    unique_ptr<Student> s1(new Student("Алексей", "S001", "alex@uni.ru", "Информатика", 2, 4.0));
    unique_ptr<Student> s2(new Student("Мария", "S002", "maria@uni.ru", "Физика", 1, 4.2));

    Student* st1 = s1.get();
    Student* st2 = s2.get();

    uni.addMember(move(s1));
    uni.addMember(move(s2));

    unique_ptr<Course> c1(new Course("PH101", "Физика-1", 5));
    unique_ptr<Course> c2(new Course("MA201", "Математика-2", 4));

    Course* course1 = c1.get();
    Course* course2 = c2.get();

    uni.addCourse(move(c1));
    uni.addCourse(move(c2));

    course1->setInstructor(p1);
    course2->setInstructor(p2);

    course1->addStudent(st1);
    course1->addStudent(st2);
    course2->addStudent(st1);

    uni.displayAllMembers();
    uni.displayAllCourses();

    cout << "Всего университетов: " << University::getTotalUniversities() << endl;
}
