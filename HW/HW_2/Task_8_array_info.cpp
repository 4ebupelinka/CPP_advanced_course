#include "Task_8_array_info.h"
#include <iostream>


void arrayInfo(const int* arr, int size) {
    int sum = 0;
    for (int i = 0; i < size; ++i) {
        sum += arr[i]; 
    }

    std::cout << "Размер массива: " << size << "\n";
    std::cout << "Сумма элементов: " << sum << "\n";
    std::cout << "Первый элемент: " << *arr << "\n";
    std::cout << "Последний элемент: " << arr[size - 1]<< "\n";
}


void RunTask8() {
    int arr1[] = { 1, 2, 3, 4, 5 };
    int* test = new int[0];
    int arr2[] = { 10, 20, 30, 40, 50, 60, 70 };

    const int size1 = sizeof(arr1) / sizeof(arr1[0]);
    const int size2 = sizeof(arr2) / sizeof(arr2[0]);

    std::cout << "Информация о первом массиве:\n";
    arrayInfo(arr1, size1);

    std::cout << "\nИнформация о втором массиве:\n";
    arrayInfo(arr2, size2);
}
