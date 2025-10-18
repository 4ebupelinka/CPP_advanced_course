#include <iostream>
#include <string>
using namespace std;

class BankAccount {
private:
    string accountNumber;
    string ownerName;
    double balance;
    static int totalAccounts;           // Общее количество счетов
    static double totalBankBalance;     // Общий баланс банка
    const double MIN_BALANCE = 10.0;    // Минимальный баланс    

public:
    BankAccount(const string& accNumber, const string& owner, double initialBalance)
        : accountNumber(accNumber), ownerName(owner), balance(initialBalance) {
        totalAccounts++;
        totalBankBalance += balance;
        cout << "Счет " << accountNumber << " открыт. Баланс: " << balance << " руб." << endl;
    }

    ~BankAccount() {
        totalAccounts--;
        totalBankBalance -= balance;
        cout << "Счет " << accountNumber << " закрыт." << endl;
    }

    void deposit(double amount) {
        if (amount > 0.0) {
            balance += amount;
            totalBankBalance += amount;
            cout << "На счет " << accountNumber << " зачислено " << amount << " руб." << endl;
        }
        else {
            cout << "Сумма для зачисления должна быть положительной." << endl;
        }
    }

    void withdraw(double amount) {
        if (amount > 0.0 && balance - amount >= MIN_BALANCE) {
            balance -= amount;
            totalBankBalance -= amount;
            cout << "Со счета " << accountNumber << " снято " << amount << " руб." << endl;
        }
        else {
            cout << "Ошибка: недостаточно средств или превышен минимальный баланс ("
                << MIN_BALANCE << " руб.)." << endl;
        }
    }

    void displayAccountInfo() const {
        cout << "==============================" << endl;
        cout << "Номер счета: " << accountNumber << endl;
        cout << "Владелец: " << ownerName << endl;
        cout << "Баланс: " << balance << " руб." << endl;
        cout << "==============================" << endl;
    }

    static int getTotalAccounts() {
        return totalAccounts;
    }

    static double getTotalBankBalance() {
        return totalBankBalance;
    }

    static double getAverageBalance() {
        if (totalAccounts == 0) {
            return 0.0;
        }
        return totalBankBalance / totalAccounts;
    }
};

int BankAccount::totalAccounts = 0;
double BankAccount::totalBankBalance = 0.0;

void Task_6() {
    cout << "Открываем три счета..." << endl;
    BankAccount account1("A001", "Иванов Иван", 500.0);
    BankAccount account2("A002", "Петров Петр", 1000.0);
    BankAccount account3("A003", "Сидоров Сидор", 2000.0);

    account1.displayAccountInfo();
    account2.displayAccountInfo();
    account3.displayAccountInfo();

    cout << "==============================" << endl;
    cout << "Общее количество счетов: " << BankAccount::getTotalAccounts() << endl;
    cout << "Общий баланс банка: " << BankAccount::getTotalBankBalance() << " руб." << endl;
    cout << "Средний баланс: " << BankAccount::getAverageBalance() << " руб." << endl;

    cout << "==============================" << endl;
    cout << "Выполняем операции по счетам..." << endl;
    account1.deposit(500.0);
    account2.withdraw(400.0);
    account3.withdraw(1950.0); 

    cout << "==============================" << endl;
    cout << "Общее количество счетов: " << BankAccount::getTotalAccounts() << endl;
    cout << "Общий баланс банка: " << BankAccount::getTotalBankBalance() << " руб." << endl;
    cout << "Средний баланс: " << BankAccount::getAverageBalance() << " руб." << endl;

    cout << "==============================" << endl;
    cout << "Закрытие счетов происходит автоматически при выходе из функции." << endl;
}
