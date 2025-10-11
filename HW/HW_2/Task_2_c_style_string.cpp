#include "Task_2_c_style_string.h"
#include <iostream>
#include <limits>

int GetStringLength(const char* str) {
    int length = 0;
    while (*(str + length) != '\0') {
        ++length;
    }
    return length;
}

void ReverseString(char* str, int length) {
    int left = 0;
    int right = length - 1;
    char temp;
    while (left < right) {
        temp = *(str + left);
        *(str + left) = *(str + right);
        *(str + right) = temp;

        ++left;
        --right;
    }
}

int CountCharacter(const char* str, char target, int length) {
    int count = 0;
    for (int i = 0; i < length; ++i) {
        if (*(str + i) == target) {
            ++count;
        }
    }
    return count;
}

void RunTask2() {
    const int MAX_SIZE = 256;
    char input[MAX_SIZE];

    std::cout << "Введите строку (максимум 255 символов), ТОЛЬКО ЛАТИНИЦА: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.getline(input, MAX_SIZE);

    int length = GetStringLength(input);
    std::cout << "Длина строки: " << length << "\n";

    ReverseString(input, length);
    std::cout << "Перевёрнутая строка: " << input << "\n";

    char symbol;
    std::cout << "Введите символ для подсчёта вхождений: ";
    std::cin >> symbol;

    int count = CountCharacter(input, symbol, length);
    std::cout << "Количество вхождений символа '" << symbol << "': " << count << "\n";

}
