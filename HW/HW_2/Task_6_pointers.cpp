#include "Task_6_pointers.h"
#include <iostream>

void fillFibonacci(int* arr, int size) {
    if (size <= 0) {
        return;
    }

    *arr = 0; 
    if (size > 1) {
        *(arr + 1) = 1; 
    }

    for (int i = 2; i < size; ++i) {
        *(arr + i) = *(arr + i - 1) + *(arr + i - 2);
    }
}

int sumArray(const int* arr, int size) {
    int sum = 0;
    const int* p = arr;
    for (int i = 0; i < size; ++i) {
        sum += *(p + i);
    }
    return sum;
}

int findMin(const int* arr, int size) {
    if (size <= 0) return 0;
    const int* p = arr;
    int minVal = *p;
    for (int i = 1; i < size; ++i) {
        if (*(p + i) < minVal) {
            minVal = *(p + i);
        }
    }
    return minVal;
    //return 0;
}

void reverseCopy(const int* source, int* dest, int size) {
    for (int i = 0; i < size; ++i) {
        *(dest + i) = *(source + (size - 1 - i));
    }
}

void printArray(const int* arr, int size) {
    for (int i = 0; i < size; ++i) {
        std::cout << *(arr + i) << " ";
    }
    std::cout << "\n";
}

void RunTask6() {
    const int SIZE = 2;
    int arr1[SIZE];
    int arr2[SIZE];

    fillFibonacci(arr1, SIZE);

    std::cout << "Массив 1 (Фибоначчи): ";
    printArray(arr1, SIZE);

    int sum = sumArray(arr1, SIZE);
    std::cout << "Сумма элементов массива: " << sum << "\n";

    int minVal = findMin(arr1, SIZE);
    std::cout << "Минимальный элемент массива: " << minVal << "\n";

    reverseCopy(arr1, arr2, SIZE);
    std::cout << "Массив 2 (обратный порядок): ";
    printArray(arr2, SIZE);
}
