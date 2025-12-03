#include "Transaction.h"
#include <iostream>

// Инициализация статического счетчика транзакций
int Transaction::transactionCount = 0;

// Конструктор по умолчанию
Transaction::Transaction()
    : transactionId(0),
    fromAccountNumber(0),
    toAccountNumber(0),
    amount(0.0),
    dateTime(),
    type(TransactionType::Deposit)
{
}

// Конструктор с параметрами
Transaction::Transaction(int transactionId,
    int fromAccountNumber,
    int toAccountNumber,
    double amount,
    const DateTime& dateTime,
    TransactionType type)
    : transactionId(transactionId),
    fromAccountNumber(fromAccountNumber),
    toAccountNumber(toAccountNumber),
    amount(amount),
    dateTime(dateTime),
    type(type)
{
}

// Геттеры

int Transaction::GetTransactionId() const
{
    return transactionId;
}

int Transaction::GetFromAccountNumber() const
{
    return fromAccountNumber;
}

int Transaction::GetToAccountNumber() const
{
    return toAccountNumber;
}

double Transaction::GetAmount() const
{
    return amount;
}

DateTime Transaction::GetDateTime() const
{
    return dateTime;
}

TransactionType Transaction::GetTransactionType() const
{
    return type;
}

// Статические методы

int Transaction::GetTransactionCount()
{
    return transactionCount;
}

int Transaction::GenerateTransactionId()
{
    transactionCount = transactionCount + 1;
    return transactionCount;
}

// Вывод информации о транзакции

void Transaction::PrintInfo() const
{
    std::cout << "Transaction ID: " << transactionId << std::endl;
    std::cout << "From account: " << fromAccountNumber << std::endl;
    std::cout << "To account: " << toAccountNumber << std::endl;
    std::cout << "Amount: " << amount << std::endl;

    std::cout << "Date: "
        << dateTime.date.day << "."
        << dateTime.date.month << "."
        << dateTime.date.year << " "
        << dateTime.hour << ":"
        << dateTime.minute << ":"
        << dateTime.second << std::endl;

    std::cout << "Type: ";

    if (type == TransactionType::Deposit)
    {
        std::cout << "Deposit";
    }
    else if (type == TransactionType::Withdraw)
    {
        std::cout << "Withdraw";
    }
    else if (type == TransactionType::Transfer)
    {
        std::cout << "Transfer";
    }
    else
    {
        std::cout << "Unknown";
    }

    std::cout << std::endl;
}
