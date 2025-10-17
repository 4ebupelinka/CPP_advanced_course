#include "Task_4_swap.h"
#include <iostream>


void swapValues(int a, int b) {
    int temp = a;
    a = b;
    b = temp;
}


void swapValues(int* a, int* b) {
    if (a == nullptr || b == nullptr) {
        return;
    }
    int temp = *a;
    *a = *b;
    *b = temp;
}


void swapValues(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}


void swapByValue(int a, int b) {
    int temp = a;
    a = b;
    b = temp;
}


void swapByPointer(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}


void swapByReference(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}


void RunTask4() {
    int x = 10;
    int y = 20;

    std::cout << "Начальные значения:\n";
    std::cout << "x = " << x << ", y = " << y << "\n";


    swapByValue(x, y);
    std::cout << "\nПосле swapValues(x, y) (по значению):\n";
    std::cout << "x = " << x << ", y = " << y << " (не изменились)\n";

    swapByPointer(&x, &y);
    std::cout << "\nПосле swapValues(&x, &y) (по указателю):\n";
    std::cout << "x = " << x << ", y = " << y << " (значения поменялись)\n";

    swapByReference(x, y);
    std::cout << "\nПосле swapValues(x, y) (по ссылке):\n";
    std::cout << "x = " << x << ", y = " << y << " (значения снова поменялись)\n";



    //swapValues(x, y);

    ////swapValues(static_cast<int>(x), static_cast<int>(y));
    //swapValues(&x, &y);
    //swapValues(static_cast<int&>(x), static_cast<int&>(y));
}
