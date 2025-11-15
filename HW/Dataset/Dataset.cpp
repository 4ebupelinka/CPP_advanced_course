#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>

using namespace std;

struct ThreadRunResult {
    int totalSurvived;
    int totalDead;
    double milliseconds;
};

void count_segment(const vector<int>* data,
    int startIndex,
    int endIndex,
    int* survivedCount,
    int* deadCount)
{
    int localSurvived = 0;
    int localDead = 0;

    for (int i = startIndex; i < endIndex; ++i) {
        int value = (*data)[i];
        if (value == 1) {
            localSurvived++;
        }
        else if (value == 0) {
            localDead++;
        }
    }

    *survivedCount = localSurvived;
    *deadCount = localDead;
}

ThreadRunResult run_count(const vector<int>& data, int threadCount)
{
    ThreadRunResult result;
    result.totalSurvived = 0;
    result.totalDead = 0;
    result.milliseconds = 0.0;

    int n = static_cast<int>(data.size());
    if (n == 0 || threadCount <= 0) {
        return result;
    }

    if (threadCount > n) {
        threadCount = n;
    }

    vector<thread> threads;
    threads.reserve(threadCount);

    vector<int> survivedPerThread(threadCount);
    vector<int> deadPerThread(threadCount);

    chrono::high_resolution_clock::time_point startTime =
        chrono::high_resolution_clock::now();

    for (int i = 0; i < threadCount; ++i) {
        int startIndex = i * n / threadCount;
        int endIndex = (i + 1) * n / threadCount;

        survivedPerThread[i] = 0;
        deadPerThread[i] = 0;

        threads.push_back(
            thread(
                count_segment,
                &data,
                startIndex,
                endIndex,
                &survivedPerThread[i],
                &deadPerThread[i]
            )
        );
    }

    for (int i = 0; i < static_cast<int>(threads.size()); ++i) {
        threads[i].join();
    }

    chrono::high_resolution_clock::time_point endTime =
        chrono::high_resolution_clock::now();

    chrono::duration<double, milli> diff = endTime - startTime;
    result.milliseconds = diff.count();

    for (int i = 0; i < threadCount; ++i) {
        result.totalSurvived += survivedPerThread[i];
        result.totalDead += deadPerThread[i];
    }

    return result;
}

int main()
{
    ifstream file("titanic.csv");
    if (!file.is_open()) {
        cout << "Файл" << endl;
        return 1;
    }

    vector<int> survivedValues;
    string line;

    if (!getline(file, line)) {
        cout << "Файл 2" << endl;
        return 1;
    }

    while (getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        stringstream ss(line);
        string token;

        if (!getline(ss, token, ',')) {
            continue;
        }

        if (!getline(ss, token, ',')) {
            continue;
        }

        int survivedValue = atoi(token.c_str());
        survivedValues.push_back(survivedValue);
    }

    file.close();

    cout << "Всего пассажиров (строк данных): " << survivedValues.size() << endl;
    cout << endl;

    ThreadRunResult res1 = run_count(survivedValues, 1);
    ThreadRunResult res2 = run_count(survivedValues, 2);
    ThreadRunResult res4 = run_count(survivedValues, 4);

    cout << "1 поток" << endl;
    cout << "Выживших 🏄‍♀️: " << res1.totalSurvived << endl;
    cout << "Погибших 💀: " << res1.totalDead << endl;
    cout << "Время: " << res1.milliseconds << " ms" << endl;
    cout << endl;

    cout << "2 потока" << endl;
    cout << "Выживших 🏄‍♀️: " << res2.totalSurvived << endl;
    cout << "Погибших 💀: " << res2.totalDead << endl;
    cout << "Время: " << res2.milliseconds << " ms" << endl;
    cout << endl;

    cout << "4 потока" << endl;
    cout << "Выживших 🏄‍♀️: " << res4.totalSurvived << endl;
    cout << "Погибших 💀: " << res4.totalDead << endl;
    cout << "Время: " << res4.milliseconds << " ms" << endl;
    cout << endl;

    return 0;
}
