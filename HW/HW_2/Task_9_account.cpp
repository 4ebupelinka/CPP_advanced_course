#include "Task_9_account.h"
#include <iostream>
#include <string>

struct Account {
    int number;
    double balance;
};

void deposit(Account* acc, double amount) {
    if (acc == nullptr) {
        std::cout << "Ошибка: неверный указатель на счет.\n";
        return;
    }
    if (amount <= 0) {
        std::cout << "Сумма пополнения должна быть положительной.\n";
        return;
    }

    acc->balance += amount;
    std::cout << "Счет #" << acc->number << " пополнен на " << amount
        << ". Новый баланс: " << acc->balance << "\n";
}

void withdraw(Account& acc, double amount) {
    if (amount <= 0) {
        std::cout << "Сумма снятия должна быть положительной.\n";
        return;
    }
    if (acc.balance < amount) {
        std::cout << "Недостаточно средств на счете, " << acc.number << ". Баланс: " << acc.balance << "\n";
        return;
    }

    acc.balance -= amount;
    std::cout << "Со счета #" << acc.number << " снято " << amount
        << ". Новый баланс: " << acc.balance << "\n";
}

void RunTask9() {
    Account myAccount;
    myAccount.number = 12345;
    myAccount.balance = 1000.0;

    std::cout << "Начальное состояние счета:\n";
    std::cout << "Номер: " << myAccount.number << "\n";
    std::cout << "Баланс: " << myAccount.balance << "\n\n";

    deposit(&myAccount, 500.0);   
    withdraw(myAccount, 300.0);   
    withdraw(myAccount, 2000.0);
}
