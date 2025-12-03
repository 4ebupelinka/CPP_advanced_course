#include "Client.h"
#include <iostream>

// Инициализация статического счетчика клиентов
int Client::clientCount = 0;

// Конструктор по умолчанию
Client::Client()
    : id(0),
    firstName(""),
    lastName(""),
    address(),
    registrationDate()
{
}

// Конструктор с параметрами
Client::Client(int id,
    const std::string& firstName,
    const std::string& lastName,
    const Address& address,
    const Date& registrationDate)
    : id(id),
    firstName(firstName),
    lastName(lastName),
    address(address),
    registrationDate(registrationDate)
{
}

// Виртуальный деструктор
Client::~Client()
{
}

// Геттеры

int Client::GetId() const
{
    return id;
}

std::string Client::GetFirstName() const
{
    return firstName;
}

std::string Client::GetLastName() const
{
    return lastName;
}

Address Client::GetAddress() const
{
    return address;
}

Date Client::GetRegistrationDate() const
{
    return registrationDate;
}

// Сеттеры

void Client::SetFirstName(const std::string& firstName)
{
    this->firstName = firstName;
}

void Client::SetLastName(const std::string& lastName)
{
    this->lastName = lastName;
}

void Client::SetAddress(const Address& address)
{
    this->address = address;
}

// Виртуальный метод отображения информации о клиенте

void Client::PrintInfo() const
{
    std::cout << "Client ID: " << id << std::endl;
    std::cout << "Name: " << firstName << " " << lastName << std::endl;
    std::cout << "Address: " << address.streetAndBuilding << ", "
        << address.city << ", "
        << address.postalCode << ", "
        << address.country << std::endl;
    std::cout << "Registration date: "
        << registrationDate.day << "."
        << registrationDate.month << "."
        << registrationDate.year << std::endl;
}

// Статические методы

int Client::GetClientCount()
{
    return clientCount;
}

int Client::GenerateClientId()
{
    clientCount = clientCount + 1;
    return clientCount;
}
