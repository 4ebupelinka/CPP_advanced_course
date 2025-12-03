#pragma once

#include "Types.h"

// Класс "Банковский счет"
class Account
{
public:
    Account();
    Account(int accountNumber,
        int ownerClientId,
        AccountType type,
        const Date& openDate);

    // Геттеры
    int GetAccountNumber() const;
    int GetOwnerClientId() const;
    double GetBalance() const;
    AccountType GetAccountType() const;
    Date GetOpenDate() const;
    bool IsActive() const;

    // Методы изменения статуса
    void Activate();
    void Deactivate();

    // Операции по счету
    bool Deposit(double amount);
    bool Withdraw(double amount);

    // Статические методы для счетчика/генерации номера счета
    static int GetAccountCount();
    static int GenerateAccountNumber();

private:
    int accountNumber;
    int ownerClientId;
    double balance;
    AccountType type;
    Date openDate;
    bool active;

    static int accountCount;
};