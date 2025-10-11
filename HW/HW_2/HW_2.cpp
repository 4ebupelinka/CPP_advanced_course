#include "Task_1_temperature.h"
#include "Task_2_c_style_string.h"
#include "Task_3_complex_calculator.h"
#include "Task_4_swap.h"
#include "Task_5_books.h"
#include "Task_6_pointers.h"
#include "Task_7_students.h"
#include "Task_8_array_info.h"
#include "Task_9_account.h"
#include "Task_10_sort_and_search.h"

#include <iostream>

int main() {
    int choice;

    while (true) {
        std::cout << "\n===========================\n";
        std::cout << " Выберите задание (1-10)\n";
        std::cout << " 0 - Выход\n";
        std::cout << "===========================\n";
        std::cout << "Ваш выбор: ";
        std::cin >> choice;

        switch (choice) {
        case 0:
            std::cout << "Выход из программы...\n";
            return 0;

        case 1:
            RunTask1();
            break;

        case 2:
            RunTask2();
            break;

        case 3:
            RunTask3();
            break;

        case 4:
            RunTask4();
            break;

        case 5:
            RunTask5();
            break;

        case 6:
            RunTask6();
            break;

        case 7:
            RunTask7();
            break;

        case 8:
            RunTask8();
            break;

        case 9:
            RunTask9();
            break;

        case 10:
            RunTask10();
            break;

        default:
            std::cout << "Нет такого задания 😶‍🌫️\n";
            break;
        }
    }

    return 0;
}