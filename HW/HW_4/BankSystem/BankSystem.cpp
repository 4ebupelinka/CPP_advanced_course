#include <iostream>
#include "Bank.h"
#include "Menu.h"

int main()
{
    Bank bank(BankConfig::BANK_NAME);

    std::cout << "Welcome to " << bank.GetName() << "!" << std::endl;

    RunMainMenu(bank);

    std::cout << "Exiting program..." << std::endl;

    return 0;
}
