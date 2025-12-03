#include "Bank.h"
#include <iostream>
#include <ctime>

// Вспомогательная функция: получить текущую дату
static Date GetCurrentDate()
{
    Date d;

    std::time_t now = std::time(0);
    std::tm localTime;

    // localtime_s(&destination, &source)
    if (localtime_s(&localTime, &now) == 0)
    {
        d.day = localTime.tm_mday;
        d.month = localTime.tm_mon + 1;
        d.year = localTime.tm_year + 1900;
    }
    else
    {
        d.day = 1;
        d.month = 1;
        d.year = 2000;
    }

    return d;
}


// Вспомогательная функция: получить текущие дату и время
static DateTime GetCurrentDateTime()
{
    DateTime dt;

    std::time_t now = std::time(0);
    std::tm localTime;

    if (localtime_s(&localTime, &now) == 0)
    {
        dt.date.day = localTime.tm_mday;
        dt.date.month = localTime.tm_mon + 1;
        dt.date.year = localTime.tm_year + 1900;

        dt.hour = localTime.tm_hour;
        dt.minute = localTime.tm_min;
        dt.second = localTime.tm_sec;
    }
    else
    {
        dt.date.day = 1;
        dt.date.month = 1;
        dt.date.year = 2000;
        dt.hour = 0;
        dt.minute = 0;
        dt.second = 0;
    }

    return dt;
}


// ------------------ Конструкторы / деструктор ------------------

Bank::Bank()
    : name(BankConfig::BANK_NAME),
    clients(),
    accounts(),
    transactions()
{
}

Bank::Bank(const std::string& name)
    : name(name),
    clients(),
    accounts(),
    transactions()
{
}

Bank::~Bank()
{
    // Освобождаем память всех клиентов
    std::size_t i;
    for (i = 0; i < clients.size(); i = i + 1)
    {
        delete clients[i];
        clients[i] = 0;
    }
    clients.clear();
}

// ------------------ Управление клиентами ------------------

Client* Bank::AddClient(const std::string& firstName,
    const std::string& lastName,
    const Address& address,
    bool isPremium,
    int premiumLevel,
    double discountPercent)
{
    Date registrationDate = GetCurrentDate();

    if (isPremium)
    {
        PremiumClient* premiumClient = CreatePremiumClient(firstName,
            lastName,
            address,
            registrationDate,
            premiumLevel,
            discountPercent);
        return premiumClient;
    }
    else
    {
        Client* client = CreateStandardClient(firstName,
            lastName,
            address,
            registrationDate);
        return client;
    }
}

bool Bank::RemoveClient(int clientId)
{
    if (HasActiveAccounts(clientId))
    {
        std::cout << "Error: client has active accounts. Cannot remove." << std::endl;
        return false;
    }

    std::size_t i;
    for (i = 0; i < clients.size(); i = i + 1)
    {
        if (clients[i] != 0 && clients[i]->GetId() == clientId)
        {
            delete clients[i];
            clients.erase(clients.begin() + static_cast<long>(i));
            std::cout << "Client removed successfully." << std::endl;
            return true;
        }
    }

    std::cout << "Error: client not found." << std::endl;
    return false;
}

Client* Bank::FindClientById(int clientId)
{
    std::size_t i;
    for (i = 0; i < clients.size(); i = i + 1)
    {
        if (clients[i] != 0 && clients[i]->GetId() == clientId)
        {
            return clients[i];
        }
    }

    return 0;
}

const Client* Bank::FindClientById(int clientId) const
{
    std::size_t i;
    for (i = 0; i < clients.size(); i = i + 1)
    {
        if (clients[i] != 0 && clients[i]->GetId() == clientId)
        {
            return clients[i];
        }
    }

    return 0;
}

const std::vector<Client*>& Bank::GetAllClients() const
{
    return clients;
}

bool Bank::EditClientName(int clientId,
    const std::string& newFirstName,
    const std::string& newLastName)
{
    Client* client = FindClientById(clientId);
    if (client == 0)
    {
        std::cout << "Error: client not found." << std::endl;
        return false;
    }

    client->SetFirstName(newFirstName);
    client->SetLastName(newLastName);

    std::cout << "Client name updated." << std::endl;
    return true;
}

bool Bank::EditClientAddress(int clientId,
    const Address& newAddress)
{
    Client* client = FindClientById(clientId);
    if (client == 0)
    {
        std::cout << "Error: client not found." << std::endl;
        return false;
    }

    client->SetAddress(newAddress);

    std::cout << "Client address updated." << std::endl;
    return true;
}

// ------------------ Управление счетами ------------------

Account* Bank::OpenAccount(int clientId,
    AccountType type,
    const Date& openDate)
{
    Client* client = FindClientById(clientId);
    if (client == 0)
    {
        std::cout << "Error: client not found. Cannot open account." << std::endl;
        return 0;
    }

    int accountNumber = Account::GenerateAccountNumber();
    Account newAccount(accountNumber, clientId, type, openDate);
    accounts.push_back(newAccount);

    std::cout << "Account opened. Number: " << accountNumber << std::endl;

    // Возвращаем указатель на только что добавленный счет
    if (!accounts.empty())
    {
        return &accounts[accounts.size() - 1];
    }

    return 0;
}

bool Bank::CloseAccount(int accountNumber)
{
    std::size_t i;
    for (i = 0; i < accounts.size(); i = i + 1)
    {
        if (accounts[i].GetAccountNumber() == accountNumber)
        {
            if (!accounts[i].IsActive())
            {
                std::cout << "Error: account is already inactive." << std::endl;
                return false;
            }

            if (accounts[i].GetBalance() != 0.0)
            {
                std::cout << "Error: account balance is not zero. Cannot close account." << std::endl;
                return false;
            }

            accounts[i].Deactivate();
            std::cout << "Account closed successfully." << std::endl;
            return true;
        }
    }

    std::cout << "Error: account not found." << std::endl;
    return false;
}

Account* Bank::FindAccountByNumber(int accountNumber)
{
    std::size_t i;
    for (i = 0; i < accounts.size(); i = i + 1)
    {
        if (accounts[i].GetAccountNumber() == accountNumber)
        {
            return &accounts[i];
        }
    }

    return 0;
}

const Account* Bank::FindAccountByNumber(int accountNumber) const
{
    std::size_t i;
    for (i = 0; i < accounts.size(); i = i + 1)
    {
        if (accounts[i].GetAccountNumber() == accountNumber)
        {
            return &accounts[i];
        }
    }

    return 0;
}

std::vector<Account*> Bank::GetAccountsByClientId(int clientId)
{
    std::vector<Account*> result;
    std::size_t i;

    for (i = 0; i < accounts.size(); i = i + 1)
    {
        if (accounts[i].GetOwnerClientId() == clientId)
        {
            result.push_back(&accounts[i]);
        }
    }

    return result;
}

std::vector<const Account*> Bank::GetAccountsByClientId(int clientId) const
{
    std::vector<const Account*> result;
    std::size_t i;

    for (i = 0; i < accounts.size(); i = i + 1)
    {
        if (accounts[i].GetOwnerClientId() == clientId)
        {
            result.push_back(&accounts[i]);
        }
    }

    return result;
}

const std::vector<Account>& Bank::GetAllAccounts() const
{
    return accounts;
}

// ------------------ Банковские операции ------------------

bool Bank::DepositToAccount(int accountNumber, double amount)
{
    if (amount <= 0.0)
    {
        std::cout << "Error: deposit amount must be positive." << std::endl;
        return false;
    }

    Account* account = FindAccountByNumber(accountNumber);
    if (account == 0)
    {
        std::cout << "Error: account not found." << std::endl;
        return false;
    }

    bool ok = account->Deposit(amount);
    if (ok)
    {
        AddTransaction(0, accountNumber, amount, TransactionType::Deposit);
    }

    return ok;
}

bool Bank::WithdrawFromAccount(int accountNumber, double amount)
{
    if (amount <= 0.0)
    {
        std::cout << "Error: withdraw amount must be positive." << std::endl;
        return false;
    }

    Account* account = FindAccountByNumber(accountNumber);
    if (account == 0)
    {
        std::cout << "Error: account not found." << std::endl;
        return false;
    }

    bool ok = account->Withdraw(amount);
    if (ok)
    {
        AddTransaction(accountNumber, 0, amount, TransactionType::Withdraw);
    }

    return ok;
}

bool Bank::TransferBetweenAccounts(int fromAccountNumber,
    int toAccountNumber,
    double amount)
{
    if (amount <= 0.0)
    {
        std::cout << "Error: transfer amount must be positive." << std::endl;
        return false;
    }

    if (fromAccountNumber == toAccountNumber)
    {
        std::cout << "Error: cannot transfer to the same account." << std::endl;
        return false;
    }

    Account* fromAccount = FindAccountByNumber(fromAccountNumber);
    Account* toAccount = FindAccountByNumber(toAccountNumber);

    if (fromAccount == 0 || toAccount == 0)
    {
        std::cout << "Error: one or both accounts not found." << std::endl;
        return false;
    }

    if (!fromAccount->IsActive() || !toAccount->IsActive())
    {
        std::cout << "Error: one or both accounts are inactive." << std::endl;
        return false;
    }

    if (fromAccount->GetBalance() < amount)
    {
        std::cout << "Error: Nah? you are so broke..." << std::endl;
        return false;
    }

    bool withdrawn = fromAccount->Withdraw(amount);
    if (!withdrawn)
    {
        return false;
    }

    bool deposited = toAccount->Deposit(amount);
    if (!deposited)
    {
        // Попытка отката: вернуть деньги на исходный счет
        fromAccount->Deposit(amount);
        return false;
    }

    AddTransaction(fromAccountNumber, toAccountNumber, amount, TransactionType::Transfer);
    std::cout << "Transfer completed successfully." << std::endl;

    return true;
}

// ------------------ Отчеты и аналитика ------------------

void Bank::PrintBankInfo() const
{
    std::cout << "Bank name: " << name << std::endl;
    std::cout << "Total clients: " << clients.size() << std::endl;
    std::cout << "Total accounts: " << accounts.size() << std::endl;
    std::cout << "Total transactions: " << transactions.size() << std::endl;
}

void Bank::PrintAllClients() const
{
    std::cout << "----- Clients list -----" << std::endl;

    if (clients.empty())
    {
        std::cout << "No clients registered." << std::endl;
        return;
    }

    std::size_t i;
    for (i = 0; i < clients.size(); i = i + 1)
    {
        if (clients[i] != 0)
        {
            clients[i]->PrintInfo();
            std::cout << "------------------------" << std::endl;
        }
    }
}

void Bank::PrintAllAccounts() const
{
    std::cout << "----- Accounts list -----" << std::endl;

    if (accounts.empty())
    {
        std::cout << "No accounts opened." << std::endl;
        return;
    }

    std::size_t i;
    for (i = 0; i < accounts.size(); i = i + 1)
    {
        const Account& acc = accounts[i];
        std::cout << "Account number: " << acc.GetAccountNumber() << std::endl;
        std::cout << "Owner client ID: " << acc.GetOwnerClientId() << std::endl;
        std::cout << "Balance: " << acc.GetBalance() << std::endl;
        std::cout << "Type: ";
        if (acc.GetAccountType() == AccountType::Checking)
        {
            std::cout << "Checking";
        }
        else
        {
            std::cout << "Saving";
        }
        std::cout << std::endl;
        std::cout << "Open date: "
            << acc.GetOpenDate().day << "."
            << acc.GetOpenDate().month << "."
            << acc.GetOpenDate().year << std::endl;
        std::cout << "Status: ";
        if (acc.IsActive())
        {
            std::cout << "Active";
        }
        else
        {
            std::cout << "Closed";
        }
        std::cout << std::endl;
        std::cout << "------------------------" << std::endl;
    }
}

void Bank::PrintAllTransactions() const
{
    std::cout << "----- Transactions history -----" << std::endl;

    if (transactions.empty())
    {
        std::cout << "No transactions." << std::endl;
        return;
    }

    std::size_t i;
    for (i = 0; i < transactions.size(); i = i + 1)
    {
        transactions[i].PrintInfo();
        std::cout << "------------------------" << std::endl;
    }
}

void Bank::PrintStatistics() const
{
    int activeAccountsCount = 0;
    int activeClientsCount = 0;
    double totalBalance = 0.0;

    // Считаем активные счета и общий баланс
    std::size_t i;
    for (i = 0; i < accounts.size(); i = i + 1)
    {
        if (accounts[i].IsActive())
        {
            activeAccountsCount = activeAccountsCount + 1;
        }
        totalBalance = totalBalance + accounts[i].GetBalance();
    }

    // Считаем клиентов, у которых есть хотя бы один активный счет
    std::size_t j;
    for (j = 0; j < clients.size(); j = j + 1)
    {
        if (clients[j] != 0)
        {
            int clientId = clients[j]->GetId();
            if (HasActiveAccounts(clientId))
            {
                activeClientsCount = activeClientsCount + 1;
            }
        }
    }

    std::cout << "----- Bank statistics -----" << std::endl;
    std::cout << "Active clients: " << activeClientsCount << std::endl;
    std::cout << "Active accounts: " << activeAccountsCount << std::endl;
    std::cout << "Total balance on all accounts: " << totalBalance << std::endl;
}

// ------------------ Прочее ------------------

const std::string& Bank::GetName() const
{
    return name;
}

// ------------------ Приватные методы ------------------

Client* Bank::CreateStandardClient(const std::string& firstName,
    const std::string& lastName,
    const Address& address,
    const Date& registrationDate)
{
    int id = Client::GenerateClientId();
    Client* client = new Client(id, firstName, lastName, address, registrationDate);
    clients.push_back(client);

    std::cout << "Standard client added. ID: " << id << std::endl;

    return client;
}

PremiumClient* Bank::CreatePremiumClient(const std::string& firstName,
    const std::string& lastName,
    const Address& address,
    const Date& registrationDate,
    int premiumLevel,
    double discountPercent)
{
    int id = Client::GenerateClientId();
    PremiumClient* client = new PremiumClient(id,
        firstName,
        lastName,
        address,
        registrationDate,
        premiumLevel,
        discountPercent);
    clients.push_back(client);

    std::cout << "Premium client added. ID: " << id << std::endl;

    return client;
}

bool Bank::HasActiveAccounts(int clientId) const
{
    std::size_t i;
    for (i = 0; i < accounts.size(); i = i + 1)
    {
        if (accounts[i].GetOwnerClientId() == clientId &&
            accounts[i].IsActive())
        {
            return true;
        }
    }

    return false;
}

void Bank::AddTransaction(int fromAccountNumber,
    int toAccountNumber,
    double amount,
    TransactionType type)
{
    int id = Transaction::GenerateTransactionId();
    DateTime dt = GetCurrentDateTime();

    Transaction t(id,
        fromAccountNumber,
        toAccountNumber,
        amount,
        dt,
        type);

    transactions.push_back(t);
}
