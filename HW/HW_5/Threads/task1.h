#pragma once

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>
#include <random>

class VectorSumCalculator {
private:
    std::vector<int> data;
    std::mutex sum_mutex;

    // Вспомогательная функция для частичной суммы в подотрезке
    void partialSum(size_t start_index, size_t end_index, long long& total_sum) {
        long long local_sum = 0;
        size_t i;
        for (i = start_index; i < end_index; ++i) {
            local_sum += data[i];
        }

        // Защищаем добавление к общей сумме
        sum_mutex.lock();
        total_sum += local_sum;
        sum_mutex.unlock();
    }

public:
    // Конструктор: заполняем вектор случайными числами [1; 100]
    VectorSumCalculator(size_t size) {
        data.resize(size);

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(1, 100);

        size_t i;
        for (i = 0; i < size; ++i) {
            data[i] = dist(gen);
        }
    }

    // Однопоточное вычисление суммы
    long long calculateSingleThreaded() {
        long long sum = 0;
        size_t i;
        for (i = 0; i < data.size(); ++i) {
            sum += data[i];
        }
        return sum;
    }

    // Многопоточное вычисление суммы
    long long calculateMultiThreaded(int num_threads) {
        if (num_threads <= 0) {
            num_threads = 1;
        }

        long long total_sum = 0;
        std::vector<std::thread> threads;
        threads.reserve(static_cast<size_t>(num_threads));

        size_t length = data.size();
        size_t block_size = length / static_cast<size_t>(num_threads);
        size_t start = 0;
        int i;

        for (i = 0; i < num_threads; ++i) {
            size_t end = start + block_size;
            if (i == num_threads - 1) {
                end = length; 
            }

            threads.push_back(std::thread(
                &VectorSumCalculator::partialSum,
                this,
                start,
                end,
                std::ref(total_sum)
            ));

            start = end;
        }

        // Ждем завершения всех потоков
        size_t t;
        for (t = 0; t < threads.size(); ++t) {
            if (threads[t].joinable()) {
                threads[t].join();
            }
        }

        return total_sum;
    }
};

inline void runTask1() {
    const size_t vector_size = 10000000; 
    VectorSumCalculator calculator(vector_size);

    std::cout << "=== Task 1: Vector Sum Calculator ===" << std::endl;

    // Однопоточный вариант
    std::chrono::high_resolution_clock::time_point start_single =
        std::chrono::high_resolution_clock::now();

    long long single_result = calculator.calculateSingleThreaded();

    std::chrono::high_resolution_clock::time_point end_single =
        std::chrono::high_resolution_clock::now();

    std::chrono::milliseconds duration_single =
        std::chrono::duration_cast<std::chrono::milliseconds>(end_single - start_single);

    // Многопоточный вариант (4 потока)
    std::chrono::high_resolution_clock::time_point start_multi =
        std::chrono::high_resolution_clock::now();

    long long multi_result = calculator.calculateMultiThreaded(4);

    std::chrono::high_resolution_clock::time_point end_multi =
        std::chrono::high_resolution_clock::now();

    std::chrono::milliseconds duration_multi =
        std::chrono::duration_cast<std::chrono::milliseconds>(end_multi - start_multi);

    std::cout << "Single-threaded result: " << single_result
        << ", time: " << duration_single.count() << " ms" << std::endl;
    std::cout << "Multi-threaded  result: " << multi_result
        << ", time: " << duration_multi.count() << " ms" << std::endl;
    std::cout << std::endl;
}

