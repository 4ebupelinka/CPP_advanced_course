#include <iostream>
#include <vector>
#include <stdexcept>
#include <string>
using namespace std;

template<typename T>
class Stack {
private:
    vector<T> elements;
    int capacity;

public:
    Stack(int size = 10) : capacity(size) {}

    void push(const T& element) {
        if (isFull()) {
            throw overflow_error("Стек переполнен");
        }
        elements.push_back(element);
    }

    T pop() {
        if (isEmpty()) {
            throw underflow_error("Стек пуст");
        }
        T topElement = elements.back();
        elements.pop_back();
        return topElement;
    }

    T top() const {
        if (isEmpty()) {
            throw underflow_error("Стек пуст");
        }
        return elements.back();
    }

    bool isEmpty() const {
        return elements.empty();
    }

    bool isFull() const {
        return static_cast<int>(elements.size()) >= capacity;
    }

    int size() const {
        return static_cast<int>(elements.size());
    }

    void display() const {
        cout << "Стек: ";
        for (size_t i = 0; i < elements.size(); i++) {
            cout << elements[i] << " ";
        }
        cout << endl;
    }
};

template<typename T>
class Queue {
private:
    vector<T> elements;
    int capacity;

public:
    Queue(int size = 10) : capacity(size) {}

    void enqueue(const T& element) {
        if (isFull()) {
            throw overflow_error("Очередь переполнена");
        }
        elements.push_back(element);
    }

    T dequeue() {
        if (isEmpty()) {
            throw underflow_error("Очередь пуста");
        }
        T frontElement = elements.front();
        elements.erase(elements.begin());
        return frontElement;
    }

    T front() const {
        if (isEmpty()) {
            throw underflow_error("Очередь пуста");
        }
        return elements.front();
    }

    bool isEmpty() const {
        return elements.empty();
    }

    bool isFull() const {
        return static_cast<int>(elements.size()) >= capacity;
    }

    int size() const {
        return static_cast<int>(elements.size());
    }

    void display() const {
        cout << "Очередь: ";
        for (size_t i = 0; i < elements.size(); i++) {
            cout << elements[i] << " ";
        }
        cout << endl;
    }
};

void Task_9() {
    cout << "==============================" << endl;
    cout << "Тест стека с int" << endl;
    Stack<int> intStack(5);
    intStack.push(10);
    intStack.push(20);
    intStack.push(30);
    intStack.display();
    cout << "Верхний элемент: " << intStack.top() << endl;
    cout << "Удален элемент: " << intStack.pop() << endl;
    intStack.display();

    cout << "==============================" << endl;
    cout << "Тест очереди с double" << endl;
    Queue<double> doubleQueue(5);
    doubleQueue.enqueue(1.1);
    doubleQueue.enqueue(2.2);
    doubleQueue.enqueue(3.3);
    doubleQueue.display();
    cout << "Первый элемент: " << doubleQueue.front() << endl;
    cout << "Удален элемент: " << doubleQueue.dequeue() << endl;
    doubleQueue.display();

    cout << "==============================" << endl;
    cout << "Тест стека со string" << endl;
    Stack<string> stringStack(3);
    stringStack.push("applum");
    stringStack.push("bananum");
    stringStack.push("coconat");
    stringStack.display();
    cout << "Верхний элемент: " << stringStack.top() << endl;
    stringStack.pop();
    stringStack.display();
}
