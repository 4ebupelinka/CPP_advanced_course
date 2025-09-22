#include <iostream>
using namespace std;

// Собственное пространство имен
namespace MyMath {
    const double PI = 3.14159;

    double square(double x) {
        return x * x;
    }

    double cube(double x) {
        return x * x * x;
    }
}

namespace Geometry {
    const double PI = 3.14; // Другое пространство имен - другое PI

    double circleArea(double radius) {
        return PI * radius * radius;
    }
}

int main() {
    // Использование пространств имен
    cout << "MyMath::PI = " << MyMath::PI << endl;
    cout << "Geometry::PI = " << Geometry::PI << endl;

    cout << "Квадрат 5: " << MyMath::square(5) << endl;
    cout << "Куб 3: " << MyMath::cube(3) << endl;
    cout << "Площадь круга: " << Geometry::circleArea(2) << endl;

    // Можно создать псевдоним
    namespace MM = MyMath;
    cout << "Через псевдоним: " << MM::square(4) << endl;

    return 0;
}