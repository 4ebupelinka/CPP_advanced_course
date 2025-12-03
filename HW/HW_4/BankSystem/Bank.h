#pragma once

#include <string>
#include <vector>

#include "Types.h"
#include "Client.h"
#include "PremiumClient.h"
#include "Account.h"
#include "Transaction.h"

// Класс "Банк" (управляющий)
class Bank
{
public:
    Bank();
    explicit Bank(const std::string& name);

    ~Bank();

    // --- Управление клиентами ---

    // Добавление нового клиента (обычного или премиум)
    Client* AddClient(const std::string& firstName,
        const std::string& lastName,
        const Address& address,
        bool isPremium,
        int premiumLevel,
        double discountPercent);

    // Удаление клиента (если нет активных счетов)
    bool RemoveClient(int clientId);

    // Поиск клиента по идентификатору
    Client* FindClientById(int clientId);
    const Client* FindClientById(int clientId) const;

    // Получение списка всех клиентов
    const std::vector<Client*>& GetAllClients() const;

    // Редактирование данных клиента
    bool EditClientName(int clientId,
        const std::string& newFirstName,
        const std::string& newLastName);

    bool EditClientAddress(int clientId,
        const Address& newAddress);

    // --- Управление банковскими счетами ---

    // Открытие счета
    Account* OpenAccount(int clientId,
        AccountType type,
        const Date& openDate);

    // Закрытие счета (при нулевом балансе)
    bool CloseAccount(int accountNumber);

    // Поиск счета по номеру
    Account* FindAccountByNumber(int accountNumber);
    const Account* FindAccountByNumber(int accountNumber) const;

    // Получение всех счетов конкретного клиента
    std::vector<Account*> GetAccountsByClientId(int clientId);
    std::vector<const Account*> GetAccountsByClientId(int clientId) const;

    // Получение списка всех счетов
    const std::vector<Account>& GetAllAccounts() const;

    // --- Банковские операции ---

    // Внесение средств
    bool DepositToAccount(int accountNumber, double amount);

    // Снятие средств
    bool WithdrawFromAccount(int accountNumber, double amount);

    // Перевод между счетами
    bool TransferBetweenAccounts(int fromAccountNumber,
        int toAccountNumber,
        double amount);

    // --- Отчеты и аналитика ---

    void PrintBankInfo() const;
    void PrintAllClients() const;
    void PrintAllAccounts() const;
    void PrintAllTransactions() const;
    void PrintStatistics() const;

    // --- Прочее ---

    const std::string& GetName() const;

private:
    std::string name;
    std::vector<Client*> clients;
    std::vector<Account> accounts;
    std::vector<Transaction> transactions;

    // Вспомогательные методы

    Client* CreateStandardClient(const std::string& firstName,
        const std::string& lastName,
        const Address& address,
        const Date& registrationDate);

    PremiumClient* CreatePremiumClient(const std::string& firstName,
        const std::string& lastName,
        const Address& address,
        const Date& registrationDate,
        int premiumLevel,
        double discountPercent);

    bool HasActiveAccounts(int clientId) const;

    void AddTransaction(int fromAccountNumber,
        int toAccountNumber,
        double amount,
        TransactionType type);
};

