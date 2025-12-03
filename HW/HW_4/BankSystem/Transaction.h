#pragma once

#include "Types.h"

// Класс "Транзакция"
class Transaction
{
public:
    Transaction();
    Transaction(int transactionId,
        int fromAccountNumber,
        int toAccountNumber,
        double amount,
        const DateTime& dateTime,
        TransactionType type);

    int GetTransactionId() const;
    int GetFromAccountNumber() const;
    int GetToAccountNumber() const;
    double GetAmount() const;
    DateTime GetDateTime() const;
    TransactionType GetTransactionType() const;

    static int GetTransactionCount();
    static int GenerateTransactionId();

    void PrintInfo() const;

private:
    int transactionId;
    int fromAccountNumber;
    int toAccountNumber;
    double amount;
    DateTime dateTime;
    TransactionType type;

    static int transactionCount;
};


