#include <iostream>
#include <string>
using namespace std;

class Vehicle {
protected:
    string brand;
    string model;
    int year;
    double fuelLevel;

public:
    Vehicle(string b, string m, int y) : brand(b), model(m), year(y), fuelLevel(100.0) {}
    virtual ~Vehicle() {}

    virtual void startEngine() = 0;
    virtual void stopEngine() = 0;
    virtual void refuel(double amount) = 0;

    virtual void displayInfo() const {
        cout << brand << " " << model << " (" << year << ")" << endl;
        cout << "Уровень топлива: " << fuelLevel << "%" << endl;
    }

    double getFuelLevel() const {
        return fuelLevel;
    }

    void setFuelLevel(double level) {
        if (level >= 0.0 && level <= 100.0) {
            fuelLevel = level;
        }
    }
};

class Car : public Vehicle {
private:
    int doors;
    string transmission;
    bool engineRunning;

public:
    Car(string b, string m, int y, int d, string trans)
        : Vehicle(b, m, y), doors(d), transmission(trans), engineRunning(false) {
    }

    void startEngine() {
        if (!engineRunning) {
            engineRunning = true;
            cout << brand << " " << model << ": двигатель запущен." << endl;
        }
        else {
            cout << brand << " " << model << ": двигатель уже работает." << endl;
        }
    }

    void stopEngine() {
        if (engineRunning) {
            engineRunning = false;
            cout << brand << " " << model << ": двигатель остановлен." << endl;
        }
        else {
            cout << brand << " " << model << ": двигатель уже выключен." << endl;
        }
    }

    void refuel(double amount) {
        if (amount > 0.0) {
            double newLevel = fuelLevel + amount;
            if (newLevel > 100.0) {
                newLevel = 100.0;
            }
            fuelLevel = newLevel;
            cout << brand << " " << model << ": заправлено. Топливо: " << fuelLevel << "%" << endl;
        }
    }

    void displayInfo() const {
        cout << "[Автомобиль]" << endl;
        Vehicle::displayInfo();
        cout << "Количество дверей: " << doors << endl;
        cout << "Коробка передач: " << transmission << endl;
        cout << "Состояние двигателя: " << (engineRunning ? "включен" : "выключен") << endl;
    }
};

class Motorcycle : public Vehicle {
private:
    bool hasFairing;
    bool engineRunning;

public:
    Motorcycle(string b, string m, int y, bool fairing)
        : Vehicle(b, m, y), hasFairing(fairing), engineRunning(false) {
    }

    void startEngine() {
        if (!engineRunning) {
            engineRunning = true;
            cout << brand << " " << model << ": двигатель запущен." << endl;
        }
        else {
            cout << brand << " " << model << ": двигатель уже работает." << endl;
        }
    }

    void stopEngine() {
        if (engineRunning) {
            engineRunning = false;
            cout << brand << " " << model << ": двигатель остановлен." << endl;
        }
        else {
            cout << brand << " " << model << ": двигатель уже выключен." << endl;
        }
    }

    void refuel(double amount) {
        if (amount > 0.0) {
            double newLevel = fuelLevel + amount;
            if (newLevel > 100.0) {
                newLevel = 100.0;
            }
            fuelLevel = newLevel;
            cout << brand << " " << model << ": заправлено. Топливо: " << fuelLevel << "%" << endl;
        }
    }

    void wheelie() {
        cout << brand << " " << model << " делает вилли!" << endl;
    }

    void displayInfo() const {
        cout << "[Мотоцикл]" << endl;
        Vehicle::displayInfo();
        cout << "Наличие обтекателя: " << (hasFairing ? "Да" : "Нет") << endl;
        cout << "Состояние двигателя: " << (engineRunning ? "включен" : "выключен") << endl;
    }
};

void Task_4() {
    Vehicle* vehicles[2];

    vehicles[0] = new Car("Opel", "Astra 1.6", 2013, 4, "Автомат");
    vehicles[1] = new Motorcycle("Yamaha", "R1", 2018, true);

    cout << "==============================" << endl;
    cout << "Демонстрация полиморфизма:" << endl;
    cout << "==============================" << endl;

    for (int i = 0; i < 2; i++) {
        vehicles[i]->displayInfo();
        vehicles[i]->startEngine();
        vehicles[i]->refuel(15.0);
        vehicles[i]->stopEngine();
        cout << "------------------------------" << endl;
    }

    Motorcycle* motoPtr = dynamic_cast<Motorcycle*>(vehicles[1]);
    if (motoPtr != NULL) {
        motoPtr->wheelie();
    }

    for (int i = 0; i < 2; i++) {
        delete vehicles[i];
    }
}
