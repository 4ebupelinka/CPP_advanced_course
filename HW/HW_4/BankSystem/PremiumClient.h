#pragma once

#include "Client.h"

// Производный класс "Премиум-клиент"
class PremiumClient : public Client
{
public:
    PremiumClient();
    PremiumClient(int id,
        const std::string& firstName,
        const std::string& lastName,
        const Address& address,
        const Date& registrationDate,
        int premiumLevel,
        double discountPercent);

    virtual ~PremiumClient();

    int GetPremiumLevel() const;
    double GetDiscountPercent() const;

    void SetPremiumLevel(int level);
    void SetDiscountPercent(double percent);

    // Переопределение виртуального метода
    virtual void PrintInfo() const;

private:
    int premiumLevel;
    double discountPercent;
};

