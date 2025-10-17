#include <iostream>
#include <vector>
#include <cmath>
using namespace std;


#ifndef PI
#define PI 3.14159265358979323846
#endif


class Shape {
protected:
    string shapeName;
    string shapeColor;

public:
    Shape(const string& name, const string& color)
        : shapeName(name), shapeColor(color) {
    }

    virtual ~Shape() {}

    virtual double calculateArea() const = 0;
    virtual double calculatePerimeter() const = 0;
    virtual void draw() const = 0;

    virtual void displayInfo() const {
        cout << "Фигура: " << shapeName << ", Цвет: " << shapeColor << endl;
    }
};

class Circle : public Shape {
private:
    double radius;

public:
    Circle(const string& color, double radiusValue)
        : Shape("Круг", color), radius(radiusValue) {
    }

    double calculateArea() const {
        return PI * radius * radius;
    }

    double calculatePerimeter() const {
        return 2.0 * PI * radius;
    }

    void draw() const {
        cout << "[Рисуем круг радиусом " << radius << "]" << endl;
    }

    void displayInfo() const {
        Shape::displayInfo();
        cout << "Радиус: " << radius << endl;
        cout << "Площадь: " << calculateArea() << endl;
        cout << "Периметр: " << calculatePerimeter() << endl;
    }
};

class Rectangle : public Shape {
private:
    double width;
    double height;

public:
    Rectangle(const string& color, double rectangleWidth, double rectangleHeight)
        : Shape("Прямоугольник", color), width(rectangleWidth), height(rectangleHeight) {
    }

    double calculateArea() const {
        return width * height;
    }

    double calculatePerimeter() const {
        return 2.0 * (width + height);
    }

    void draw() const {
        cout << "[Рисуем прямоугольник " << width << " x " << height << "]" << endl;
    }

    void displayInfo() const {
        Shape::displayInfo();
        cout << "Ширина: " << width << ", Высота: " << height << endl;
        cout << "Площадь: " << calculateArea() << endl;
        cout << "Периметр: " << calculatePerimeter() << endl;
    }
};

class Triangle : public Shape {
private:
    double sideA;
    double sideB;
    double sideC;

public:
    Triangle(const string& color, double a, double b, double c)
        : Shape("Треугольник", color), sideA(a), sideB(b), sideC(c) {
    }

    double calculateArea() const {
        double semiPerimeter = (sideA + sideB + sideC) / 2.0;
        double area = sqrt(semiPerimeter * (semiPerimeter - sideA) * (semiPerimeter - sideB) * (semiPerimeter - sideC));
        return area;
    }

    double calculatePerimeter() const {
        return sideA + sideB + sideC;
    }

    void draw() const {
        cout << "[Рисуем треугольник со сторонами " << sideA << ", " << sideB << ", " << sideC << "]" << endl;
    }

    void displayInfo() const {
        Shape::displayInfo();
        cout << "Стороны: " << sideA << ", " << sideB << ", " << sideC << endl;
        cout << "Площадь: " << calculateArea() << endl;
        cout << "Периметр: " << calculatePerimeter() << endl;
    }
};

void Task_3() {
    vector<Shape*> shapeCollection;
    shapeCollection.push_back(new Circle("Красный", 5.0));
    shapeCollection.push_back(new Rectangle("Синий", 4.0, 6.0));
    shapeCollection.push_back(new Triangle("Зеленый", 3.0, 4.0, 5.0));

    cout << "==============================" << endl;
    cout << "Демонстрация полиморфизма:" << endl;
    cout << "==============================" << endl;

    for (size_t i = 0; i < shapeCollection.size(); i++) {
        shapeCollection[i]->displayInfo();
        shapeCollection[i]->draw();
        cout << "------------------------------" << endl;
    }

    for (size_t i = 0; i < shapeCollection.size(); i++) {
        delete shapeCollection[i];
    }

    shapeCollection.clear();
}
