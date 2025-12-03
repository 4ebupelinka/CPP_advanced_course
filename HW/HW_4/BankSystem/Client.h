#pragma once


#include <string>
#include "Types.h"

// Базовый класс "Клиент"
class Client
{
public:
    Client();
    Client(int id,
        const std::string& firstName,
        const std::string& lastName,
        const Address& address,
        const Date& registrationDate);

    virtual ~Client();

    // Геттеры
    int GetId() const;
    std::string GetFirstName() const;
    std::string GetLastName() const;
    Address GetAddress() const;
    Date GetRegistrationDate() const;

    // Сеттеры
    void SetFirstName(const std::string& firstName);
    void SetLastName(const std::string& lastName);
    void SetAddress(const Address& address);

    // Виртуальный метод для отображения информации о клиенте
    virtual void PrintInfo() const;

    // Статические методы для работы со счетчиком клиентов
    static int GetClientCount();
    static int GenerateClientId();

protected:
    int id;
    std::string firstName;
    std::string lastName;
    Address address;
    Date registrationDate;

private:
    static int clientCount;
};
    
