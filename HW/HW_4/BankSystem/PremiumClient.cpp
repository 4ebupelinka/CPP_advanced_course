#include "PremiumClient.h"
#include <iostream>

// Конструктор по умолчанию
PremiumClient::PremiumClient()
    : Client(),
    premiumLevel(0),
    discountPercent(0.0)
{
}

// Конструктор с параметрами
PremiumClient::PremiumClient(int id,
    const std::string& firstName,
    const std::string& lastName,
    const Address& address,
    const Date& registrationDate,
    int premiumLevel,
    double discountPercent)
    : Client(id, firstName, lastName, address, registrationDate),
    premiumLevel(premiumLevel),
    discountPercent(discountPercent)
{
}

// Виртуальный деструктор
PremiumClient::~PremiumClient()
{
}

int PremiumClient::GetPremiumLevel() const
{
    return premiumLevel;
}

double PremiumClient::GetDiscountPercent() const
{
    return discountPercent;
}

void PremiumClient::SetPremiumLevel(int level)
{
    premiumLevel = level;
}

void PremiumClient::SetDiscountPercent(double percent)
{
    discountPercent = percent;
}

// Переопределение виртуального метода PrintInfo

void PremiumClient::PrintInfo() const
{
    // Сначала выводим базовую информацию о клиенте
    Client::PrintInfo();

    // Затем добавляем данные о премиум-статусе
    std::cout << "Premium level: " << premiumLevel << std::endl;
    std::cout << "Discount percent: " << discountPercent << std::endl;
}
