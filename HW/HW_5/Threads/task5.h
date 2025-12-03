#pragma once

#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <future>
#include <vector>

// -------------------- Базовый класс задачи --------------------

class ITask {
public:
    virtual void execute() = 0;
    virtual ~ITask() {}
};

// Обёртка для packaged_task
template<typename T>
class TaskWrapper : public ITask {
private:
    std::packaged_task<T()> task;
public:
    TaskWrapper(std::packaged_task<T()> t) : task(std::move(t)) {}
    void execute() {
        task();
    }
};

// ------------------------ ThreadPool -------------------------

class ThreadPool {
private:
    std::vector<std::thread> workers;
    std::queue<ITask*> tasks;

    std::mutex mutex;
    std::condition_variable cond;
    bool stop;

    void workerLoop() {
        for (;;) {
            ITask* task = NULL;

            {
                std::unique_lock<std::mutex> lock(mutex);

                while (!stop && tasks.empty()) {
                    cond.wait(lock);
                }

                if (stop && tasks.empty()) {
                    return;
                }

                task = tasks.front();
                tasks.pop();
            }

            if (task != NULL) {
                task->execute();
                delete task;
            }
        }
    }

public:
    ThreadPool(int n) : stop(false) {
        int i;
        for (i = 0; i < n; i++) {
            workers.push_back(std::thread(&ThreadPool::workerLoop, this));
        }
    }

    template<typename Func>
    std::future<typename std::result_of<Func()>::type> submit(Func f) {
        typedef typename std::result_of<Func()>::type R;

        std::packaged_task<R()> task(f);
        std::future<R> future = task.get_future();

        TaskWrapper<R>* wrapper = new TaskWrapper<R>(std::move(task));

        {
            std::unique_lock<std::mutex> lock(mutex);
            tasks.push(wrapper);
        }

        cond.notify_one();
        return future;
    }

    ~ThreadPool() {
        {
            std::unique_lock<std::mutex> lock(mutex);
            stop = true;
        }

        cond.notify_all();

        int i;
        for (i = 0; i < workers.size(); i++) {
            if (workers[i].joinable()) {
                workers[i].join();
            }
        }

        while (!tasks.empty()) {
            delete tasks.front();
            tasks.pop();
        }
    }
};

// -------------------- Факториал --------------------

inline unsigned long long factorial(int n) {
    unsigned long long r = 1;
    int i;
    for (i = 2; i <= n; ++i) {
        r = r * (unsigned long long)i;
    }
    return r;
}

// -------------------- Демонстрация --------------------

inline void runTask5() {
    std::cout << "=== Task 5: ThreadPool (factorial) ===" << std::endl;

    ThreadPool pool(4);
    int numbers[4] = { 5, 10, 12, 15 };

    std::vector<std::future<unsigned long long> > results;

    int i;
    for (i = 0; i < 4; i++) {
        results.push_back(pool.submit(std::bind(factorial, numbers[i])));
    }

    for (i = 0; i < results.size(); i++) {
        std::cout << "factorial(" << numbers[i] << ") = "
            << results[i].get() << std::endl;
    }

    std::cout << std::endl;
}


