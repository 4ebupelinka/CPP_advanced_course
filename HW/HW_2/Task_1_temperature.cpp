#include "Task_1_temperature.h"
#include <iostream>

void InputTemperatures(double* temperatures, int days) {
    for (int i = 0; i < days; ++i) {
        std::cout << "Введите температуру за день " << (i + 1) << ": ";
        std::cin >> temperatures[i];
    }
}

double CalculateAverage(const double* temperatures, int days) {
    double sum = 0.0;
    for (int i = 0; i < days; ++i) {
        sum += temperatures[i];
    }
    return sum / days;
}

void FindMinMax(const double* temperatures, int days, double& minTemp, double& maxTemp) {
    minTemp = temperatures[0];
    maxTemp = temperatures[0];
    for (int i = 1; i < days; ++i) {
        if (temperatures[i] < minTemp) {
            minTemp = temperatures[i];
        }
        if (temperatures[i] > maxTemp) {
            maxTemp = temperatures[i];
        }
    }
}

int CountBelowAverage(const double* temperatures, int days, double average) {
    int count = 0;
    for (int i = 0; i < days; ++i) {
        if (temperatures[i] < average) {
            ++count;
        }
    }
    return count;
}

void RunTask1() {
    int days = 0;
    std::cout << "Введите количество дней для анализа: ";
    std::cin >> days;

    if (days <= 0) {
        std::cout << "Ошибка: количество дней должно быть больше нуля.\n";
        return;
    }

    double* temperatures = new double[days];

    InputTemperatures(temperatures, days);

    double average = CalculateAverage(temperatures, days);
    double minTemp = 0.0;
    double maxTemp = 0.0;
    FindMinMax(temperatures, days, minTemp, maxTemp);
    int belowAverage = CountBelowAverage(temperatures, days, average);

    std::cout << "\nРезультаты анализа:\n";
    std::cout << "Средняя температура: " << average << "\n";
    std::cout << "Минимальная температура: " << minTemp << "\n";
    std::cout << "Максимальная температура: " << maxTemp << "\n";
    std::cout << "Количество дней с температурой ниже средней: " << belowAverage << "\n";

    delete[] temperatures;
}
