#include "Menu.h"
#include "Bank.h"
#include <iostream>

static void ShowMainMenu()
{
    std::cout << std::endl;
    std::cout << "========== OOO_Skam Banking System ==========" << std::endl;
    std::cout << "1. Add client" << std::endl;
    std::cout << "2. Show all clients" << std::endl;
    std::cout << "3. Open account" << std::endl;
    std::cout << "4. Show all accounts" << std::endl;
    std::cout << "5. Deposit to account" << std::endl;
    std::cout << "6. Withdraw from account" << std::endl;
    std::cout << "7. Transfer between accounts" << std::endl;
    std::cout << "8. Show all transactions" << std::endl;
    std::cout << "0. Exit" << std::endl;
    std::cout << "=============================================" << std::endl;
    std::cout << "Choose option: ";
}

// Главное меню
void RunMainMenu(Bank& bank)
{
    bool running = true;

    while (running)
    {
        ShowMainMenu();

        int choice;
        std::cin >> choice;

        if (!std::cin)
        {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        if (choice == 1)
        {
            std::string firstName;
            std::string lastName;
            Address address;
            int isPremiumInput;
            int level;
            double discount;

            std::cout << "First name: ";
            std::cin >> firstName;

            std::cout << "Last name: ";
            std::cin >> lastName;

            std::cout << "Street and building: ";
            std::cin >> address.streetAndBuilding;

            std::cout << "City: ";
            std::cin >> address.city;

            std::cout << "Postal code: ";
            std::cin >> address.postalCode;

            std::cout << "Country: ";
            std::cin >> address.country;

            std::cout << "Is premium? (1 - yes, 0 - no): ";
            std::cin >> isPremiumInput;

            if (isPremiumInput == 1)
            {
                std::cout << "Premium level: ";
                std::cin >> level;

                std::cout << "Discount percent: ";
                std::cin >> discount;

                bank.AddClient(firstName, lastName, address, true, level, discount);
            }
            else
            {
                bank.AddClient(firstName, lastName, address, false, 0, 0.0);
            }
        }
        else if (choice == 2)
        {
            bank.PrintAllClients();
        }
        else if (choice == 3)
        {
            int clientId;
            int typeInt;

            std::cout << "Client ID: ";
            std::cin >> clientId;

            std::cout << "Account type (0 - Checking, 1 - Saving): ";
            std::cin >> typeInt;

            AccountType type = AccountType::Checking;
            if (typeInt == 1)
            {
                type = AccountType::Saving;
            }

            Date d;
            std::cout << "Open date (day month year): ";
            std::cin >> d.day >> d.month >> d.year;

            bank.OpenAccount(clientId, type, d);
        }
        else if (choice == 4)
        {
            bank.PrintAllAccounts();
        }
        else if (choice == 5)
        {
            int account;
            double amount;

            std::cout << "Account number: ";
            std::cin >> account;

            std::cout << "Amount: ";
            std::cin >> amount;

            bank.DepositToAccount(account, amount);
        }
        else if (choice == 6)
        {
            int account;
            double amount;

            std::cout << "Account number: ";
            std::cin >> account;

            std::cout << "Amount: ";
            std::cin >> amount;

            bank.WithdrawFromAccount(account, amount);
        }
        else if (choice == 7)
        {
            int fromAcc;
            int toAcc;
            double amount;

            std::cout << "From account: ";
            std::cin >> fromAcc;

            std::cout << "To account: ";
            std::cin >> toAcc;

            std::cout << "Amount: ";
            std::cin >> amount;

            bank.TransferBetweenAccounts(fromAcc, toAcc, amount);
        }
        else if (choice == 8)
        {
            bank.PrintAllTransactions();
        }
        else if (choice == 0)
        {
            running = false;
        }
    }
}
