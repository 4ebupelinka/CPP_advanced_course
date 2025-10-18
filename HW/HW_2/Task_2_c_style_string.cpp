#include "Task_2_c_style_string.h"
#include <iostream>
#include <limits>

int GetStringLength(const wchar_t* str) {
    int length = 0;
    while (*(str + length) != L'\0') {
        ++length;
    }
    return length;
}

void ReverseString(wchar_t* str, int length) {
    int left = 0;
    int right = length - 1;
    wchar_t temp;
    while (left < right) {
        temp = *(str + left);
        *(str + left) = *(str + right);
        *(str + right) = temp;

        ++left;
        --right;
    }
}

int CountCharacter(const wchar_t* str, wchar_t  target, int length) {
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
    wchar_t input[MAX_SIZE];

    std::locale::global(std::locale(""));
    std::wcin.imbue(std::locale());
    std::wcout.imbue(std::locale());

    std::wcout << L"Введите строку (максимум 255 символов), НЕ ТОЛЬКО ЛАТИНИЦА: ";
    std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::wcin.getline(input, MAX_SIZE);


    int length = GetStringLength(input);
    std::wcout << L"Длина строки: " << length << L"\n";

    ReverseString(input, length);
    std::wcout << L"Перевёрнутая строка: " << input << L"\n";

    wchar_t symbol;
    std::wcout << L"Введите символ для подсчёта вхождений: ";
    std::wcin >> symbol;

    int count = CountCharacter(input, symbol, length);
    std::wcout << L"Количество вхождений символа '" << symbol << L"': " << count << L"\n";

}
