#include "Task_3_complex_calculator.h"
#include <iostream>
#include <iomanip>

struct Complex {
    double real;
    double imag;
};

Complex add(Complex a, Complex b) {
    Complex result;
    result.real = a.real + b.real;
    result.imag = a.imag + b.imag;
    return result;
}

Complex subtract(Complex a, Complex b) {
    Complex result;
    result.real = a.real - b.real;
    result.imag = a.imag - b.imag;
    return result;
}

Complex multiply(Complex a, Complex b) {
    Complex result;
    result.real = (a.real * b.real) - (a.imag * b.imag);
    result.imag = (a.real * b.imag) + (a.imag * b.real);
    return result;
}

void print(Complex c) {
    std::cout << c.real;
    if (c.imag >= 0) {
        std::cout << " + " << c.imag << "i";
    }
    else {
        std::cout << " - " << -c.imag << "i";
    }
}

// Главная функция задачи
void RunTask3() {
    Complex c1;
    Complex c2;

    std::cout << "Введите действительную часть первого числа: ";
    std::cin >> c1.real;
    std::cout << "Введите мнимую часть первого числа: ";
    std::cin >> c1.imag;

    std::cout << "Введите действительную часть второго числа: ";
    std::cin >> c2.real;
    std::cout << "Введите мнимую часть второго числа: ";
    std::cin >> c2.imag;

    std::cout << "\nРезультаты:\n";
    std::cout << "Сумма: ";
    print(add(c1, c2));
    std::cout << "\n";

    std::cout << "Разность: ";
    print(subtract(c1, c2));
    std::cout << "\n";

    std::cout << "Произведение: ";
    print(multiply(c1, c2));
    std::cout << "\n";
}
