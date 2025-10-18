#include <iostream>
#include <string>
using namespace std;

class Complex {
private:
    double real;
    double imaginary;

public:
    Complex(double r = 0, double i = 0) : real(r), imaginary(i) {}

    double getReal() const {
        return real;
    }

    double getImaginary() const {
        return imaginary;
    }

    void setReal(double r) {
        real = r;
    }

    void setImaginary(double i) {
        imaginary = i;
    }

    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imaginary + other.imaginary);
    }

    Complex operator-(const Complex& other) const {
        return Complex(real - other.real, imaginary - other.imaginary);
    }

    Complex operator*(const Complex& other) const {
        double newReal = real * other.real - imaginary * other.imaginary;
        double newImag = real * other.imaginary + imaginary * other.real;
        return Complex(newReal, newImag);
    }

    bool operator==(const Complex& other) const {
        return (real == other.real) && (imaginary == other.imaginary);
    }

    friend ostream& operator<<(ostream& os, const Complex& c);
    friend istream& operator>>(istream& is, Complex& c);

    void display() const {
        cout << real << " + " << imaginary << "i" << endl;
    }
};

ostream& operator<<(ostream& os, const Complex& c) {
    os << c.real << " + " << c.imaginary << "i";
    return os;
}

istream& operator>>(istream& is, Complex& c) {
    cout << "Введите действительную часть: ";
    is >> c.real;
    cout << "Введите мнимую часть: ";
    is >> c.imaginary;
    return is;
}

void Task_7() {
    Complex a(3.0, 4.0);
    Complex b(1.0, 2.0);

    cout << "Комплексное число A: " << a << endl;
    cout << "Комплексное число B: " << b << endl;

    Complex sum = a + b;
    Complex difference = a - b;
    Complex product = a * b;

    cout << "A + B = " << sum << endl;
    cout << "A - B = " << difference << endl;
    cout << "A * B = " << product << endl;

    if (a == b) {
        cout << "A и B равны" << endl;
    }
    else {
        cout << "A и B не равны" << endl;
    }

    cout << "==============================" << endl;
    Complex c;
    cin >> c;
    cout << "Вы ввели: " << c << endl;
}
