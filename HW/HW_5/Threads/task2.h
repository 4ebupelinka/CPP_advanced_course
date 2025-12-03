#pragma once

#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

template<typename T>
class ThreadSafeQueue {
private:
    std::queue<T> queue;
    std::mutex mutex;
    std::condition_variable cond;
    bool is_shutdown;

public:
    ThreadSafeQueue() : is_shutdown(false) {}

    // Добавление элемента в очередь
    void push(const T& value) {
        {
            std::unique_lock<std::mutex> lock(mutex);
            queue.push(value);
        }
        cond.notify_one();
    }

    // Извлечение элемента
    // Возвращает false, если очередь закрыта и пуста
    bool pop(T& value) {
        std::unique_lock<std::mutex> lock(mutex);
        while (queue.empty() && !is_shutdown) {
            cond.wait(lock);
        }

        if (queue.empty() && is_shutdown) {
            return false;
        }

        value = queue.front();
        queue.pop();
        return true;
    }

    // Закрытие очереди
    void shutdown() {
        {
            std::unique_lock<std::mutex> lock(mutex);
            is_shutdown = true;
        }
        cond.notify_all();
    }
};

// Производитель: генерирует числа и кладёт их в очередь
inline void producer(ThreadSafeQueue<int>& queue, int count) {
    int i;
    for (i = 1; i <= count; ++i) {
        std::cout << "[Producer] Produced: " << i << std::endl;
        queue.push(i);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    // После окончания генерации закрываем очередь
    queue.shutdown();
}

// Потребитель: извлекает числа и "обрабатывает"
inline void consumer(ThreadSafeQueue<int>& queue, int id) {
    int value;
    while (queue.pop(value)) {
        std::cout << "[Consumer " << id << "] Consumed: " << value << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(30));
    }
    std::cout << "[Consumer " << id << "] Finished (queue shutdown)" << std::endl;
}

// Демонстрация задания 2
inline void runTask2() {
    std::cout << "=== Task 2: Producer-Consumer with ThreadSafeQueue ===" << std::endl;

    ThreadSafeQueue<int> queue;
    int total_items = 20;

    // Один производитель
    std::thread producer_thread(producer, std::ref(queue), total_items);

    // Три потребителя
    std::thread consumer_thread1(consumer, std::ref(queue), 1);
    std::thread consumer_thread2(consumer, std::ref(queue), 2);
    std::thread consumer_thread3(consumer, std::ref(queue), 3);

    producer_thread.join();
    consumer_thread1.join();
    consumer_thread2.join();
    consumer_thread3.join();

    std::cout << std::endl;
}

