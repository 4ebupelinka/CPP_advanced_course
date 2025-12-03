#pragma once

#include <string>

// Структура "Адрес":
// - улица и дом
// - город
// - почтовый индекс
// - страна
struct Address
{
    std::string streetAndBuilding;
    std::string city;
    std::string postalCode;
    std::string country;
};

// Структура "Дата":
// - день
// - месяц
// - год
struct Date
{
    int day;
    int month;
    int year;
};

// Простая структура "Дата и время" для транзакций
struct DateTime
{
    Date date;
    int hour;
    int minute;
    int second;
};

// Тип банковского счета
enum class AccountType
{
    Checking,   // расчетный
    Saving      // сберегательный
};

// Тип банковской операции / транзакции
enum class TransactionType
{
    Deposit,
    Withdraw,
    Transfer
};

// Конфигурация банка: имя банка OOO_Skam
namespace BankConfig
{
    static const char BANK_NAME[] = "OOO_Skam";
}

