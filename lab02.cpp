#include <iostream>

int main()
{
    double currentb = 1000.00;
    double deposit;
    double withdraw;
    int choice;

    std::cout << "Welcome to Simple ATM Simulator!" << std::endl;
    std::cout << std::endl;
    std::cout << "Your current balance is $" << currentb << std::endl;
    std::cout << std::endl;   
    std::cout << "Menu:" << std::endl;
    std::cout << "1. Check Balance" << std::endl;
    std::cout << "2. Deposit Money" << std::endl;
    std::cout << "3. Withdraw Money" << std::endl;
    std::cout << "4. Exit" << std::endl;
    std::cout << std::endl;
    std::cout << "Enter your choice ";
    std::cin >> choice;

    while (choice != 4)
    {
        if(choice == 1)
        {
            std::cout << "Your current balance is $" << currentb << std::endl;
            std::cout << std::endl;
        }
        else if(choice == 2)
        {
            std::cout << "Enter the amount to deposit ";
            std::cin >> deposit;
            currentb = currentb + deposit;
            std::cout << "Deposit succesful! Your new balance is: $" << currentb << std::endl;
            std::cout << std::endl;
        }
        else if (choice == 3)
        {
            std::cout << "Enter the amount to withdraw ";
            std::cin >> withdraw;
            currentb = currentb - withdraw;
            std::cout << "Withdraw succesful! Your new balance is: $" << currentb << std::endl;
            std::cout << std::endl;
        }
        
        std::cout << "Enter your choice ";
        std::cin >> choice;
    }
    std::cout << "Thank you for using the ATM. Goodbye!";

    
}