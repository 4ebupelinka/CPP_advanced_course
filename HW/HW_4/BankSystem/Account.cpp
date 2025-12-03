#include "Account.h"
#include <iostream>

// Инициализация статического счетчика счетов
int Account::accountCount = 0;

// Конструктор по умолчанию
Account::Account()
    : accountNumber(0),
    ownerClientId(0),
    balance(0.0),
    type(AccountType::Checking),
    openDate(),
    active(false)
{
}

// Конструктор с параметрами
Account::Account(int accountNumber,
    int ownerClientId,
    AccountType type,
    const Date& openDate)
    : accountNumber(accountNumber),
    ownerClientId(ownerClientId),
    balance(0.0),
    type(type),
    openDate(openDate),
    active(true)
{
}

// Геттеры

int Account::GetAccountNumber() const
{
    return accountNumber;
}

int Account::GetOwnerClientId() const
{
    return ownerClientId;
}

double Account::GetBalance() const
{
    return balance;
}

AccountType Account::GetAccountType() const
{
    return type;
}

Date Account::GetOpenDate() const
{
    return openDate;
}

bool Account::IsActive() const
{
    return active;
}

// Методы изменения статуса

void Account::Activate()
{
    active = true;
}

void Account::Deactivate()
{
    active = false;
}

// Операции по счету

bool Account::Deposit(double amount)
{
    if (!active)
    {
        std::cout << "Error: account is not active." << std::endl;
        return false;
    }

    if (amount <= 0.0)
    {
        std::cout << "Error: deposit amount must be positive." << std::endl;
        return false;
    }

    balance = balance + amount;
    return true;
}

bool Account::Withdraw(double amount)
{
    if (!active)
    {
        std::cout << "Error: account is not active." << std::endl;
        return false;
    }

    if (amount <= 0.0)
    {
        std::cout << "Error: withdraw amount must be positive." << std::endl;
        return false;
    }

    if (amount > balance)
    {
        std::cout << "Error: insufficient funds." << std::endl;
        return false;
    }

    balance = balance - amount;
    return true;
}

// Статические методы

int Account::GetAccountCount()
{
    return accountCount;
}

int Account::GenerateAccountNumber()
{
    accountCount = accountCount + 1;
    return accountCount;
}
