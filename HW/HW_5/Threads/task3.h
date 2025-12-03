#pragma once

#include <iostream>
#include <vector>
#include <thread>
#include <random>
#include <chrono>
#include <algorithm>

class ImageProcessor {
private:
    std::vector<std::vector<int> > image;
    int width;
    int height;

    // Обработка части строк изображения в отдельном потоке
    void processRows(int start_row, int end_row, std::vector<std::vector<int> >& result) {
        int y;
        int x;
        for (y = start_row; y < end_row; ++y) {
            for (x = 0; x < width; ++x) {
                result[y][x] = blurPixel(x, y);
            }
        }
    }

public:
    ImageProcessor(int w, int h) : width(w), height(h) {
        image.resize(height);
        int y;
        for (y = 0; y < height; ++y) {
            image[y].resize(width);
        }

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(0, 255);

        int x;
        for (y = 0; y < height; ++y) {
            for (x = 0; x < width; ++x) {
                image[y][x] = dist(gen);
            }
        }
    }

    // Фильтр размытия (усреднение 3x3 вокруг пикселя)
    int blurPixel(int x, int y) {
        int sum = 0;
        int count = 0;

        int dy;
        int dx;
        for (dy = -1; dy <= 1; ++dy) {
            for (dx = -1; dx <= 1; ++dx) {
                int nx = x + dx;
                int ny = y + dy;
                if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                    sum += image[ny][nx];
                    ++count;
                }
            }
        }

        if (count == 0) {
            return image[y][x];
        }

        return sum / count;
    }

    // Однопоточное применение фильтра
    void applyFilterSingleThread() {
        std::vector<std::vector<int> > result(height, std::vector<int>(width, 0));

        int y;
        int x;
        for (y = 0; y < height; ++y) {
            for (x = 0; x < width; ++x) {
                result[y][x] = blurPixel(x, y);
            }
        }

        image = result;
    }

    // Многопоточное применение фильтра
    void applyFilterMultiThread(int num_threads) {
        if (num_threads <= 0) {
            num_threads = 1;
        }

        std::vector<std::vector<int> > result(height, std::vector<int>(width, 0));
        std::vector<std::thread> threads;

        threads.reserve(static_cast<size_t>(num_threads));

        int rows_per_thread = height / num_threads;
        int start_row = 0;
        int i;

        for (i = 0; i < num_threads; ++i) {
            int end_row = start_row + rows_per_thread;
            if (i == num_threads - 1) {
                end_row = height; // последний поток берет остаток
            }

            threads.push_back(std::thread(
                &ImageProcessor::processRows,
                this,
                start_row,
                end_row,
                std::ref(result)
            ));

            start_row = end_row;
        }

        size_t t;
        for (t = 0; t < threads.size(); ++t) {
            if (threads[t].joinable()) {
                threads[t].join();
            }
        }

        image = result;
    }
};

// Демонстрация задания 3
inline void runTask3() {
    std::cout << "=== Task 3: Parallel Image Processing ===" << std::endl;

    int width = 800;
    int height = 600;
    ImageProcessor processor(width, height);

    // Однопоточно
    std::chrono::high_resolution_clock::time_point start_single =
        std::chrono::high_resolution_clock::now();
    processor.applyFilterSingleThread();
    std::chrono::high_resolution_clock::time_point end_single =
        std::chrono::high_resolution_clock::now();

    std::chrono::milliseconds duration_single =
        std::chrono::duration_cast<std::chrono::milliseconds>(end_single - start_single);


    // Повторно создадим объект, чтобы сравнение было честным
    ImageProcessor processor2(width, height);

    // Многопоточно
    std::chrono::high_resolution_clock::time_point start_multi =
        std::chrono::high_resolution_clock::now();
    processor2.applyFilterMultiThread(4);
    std::chrono::high_resolution_clock::time_point end_multi =
        std::chrono::high_resolution_clock::now();

    std::chrono::milliseconds duration_multi =
        std::chrono::duration_cast<std::chrono::milliseconds>(end_multi - start_multi);



    std::cout << "Single-threaded time: " << duration_single.count() << " ms" << std::endl;
    std::cout << "Multi-threaded  time: " << duration_multi.count() << " ms" << std::endl;
    std::cout << std::endl;
}

