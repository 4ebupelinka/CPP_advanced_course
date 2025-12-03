#pragma once

#include <iostream>
#include <future>
#include <random>
#include <vector>

class PiCalculator {
public:
    // Метод Монте-Карло для части вычислений
    double calculatePiPortion(int total_points) {
        if (total_points <= 0) {
            return 0.0;
        }

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<double> dist(0.0, 1.0);

        int inside_circle = 0;
        int i;
        for (i = 0; i < total_points; ++i) {
            double x = dist(gen);
            double y = dist(gen);
            double distance = x * x + y * y;
            if (distance <= 1.0) {
                ++inside_circle;
            }
        }

        double ratio = static_cast<double>(inside_circle) /
            static_cast<double>(total_points);

        return 4.0 * ratio;
    }

    // Параллельное вычисление π
    double calculatePiParallel(int total_points, int num_tasks) {
        if (num_tasks <= 0) {
            num_tasks = 1;
        }

        std::vector<std::future<double> > futures;
        futures.reserve(static_cast<size_t>(num_tasks));

        int points_per_task = total_points / num_tasks;
        int i;

        for (i = 0; i < num_tasks; ++i) {
            // std::launch::async гарантирует запуск в отдельном потоке
            std::future<double> f = std::async(
                std::launch::async,
                &PiCalculator::calculatePiPortion,
                this,
                points_per_task
            );
            futures.push_back(std::move(f));
        }

        double sum = 0.0;
        size_t t;
        for (t = 0; t < futures.size(); ++t) {
            try {
                sum += futures[t].get();
            }
            catch (const std::exception& ex) {
                std::cout << "Exception in task: " << ex.what() << std::endl;
            }
        }

        if (futures.empty()) {
            return 0.0;
        }

        double pi = sum / static_cast<double>(futures.size());
        return pi;
    }
};

// Демонстрация задания 4
inline void runTask4() {
    std::cout << "=== Task 4: Async Pi Calculation (Monte Carlo) ===" << std::endl;

    PiCalculator calculator;

    int total_points = 5000000;
    int num_tasks = 4;

    double pi_value = calculator.calculatePiParallel(total_points, num_tasks);

    std::cout << "Approximate pi = " << pi_value
        << " (total points = " << total_points
        << ", tasks = " << num_tasks << ")" << std::endl;
    std::cout << std::endl;
}

