#include <iostream>
using namespace std;
int main()
{
    char playmore = 'y';
    while (playmore == 'y' || playmore == 'Y')
    {
        int snum = rand() % 100 + 1;
        int userin;
        int maxg = 5;

        cout << "Welcome to: GUESS THAT NUMBER!!" << endl;
        cout << "A random number between 1 and 100 has been chosen" << endl;
        cout << "You have " << maxg << " attempts to guess the number" << endl;

        for (int i = 1; i <= maxg; i++)
        {
            cout << "Attempt " << i << ": Enter a guess: ";
            cin >> userin;

            if (userin == snum)
            {
                cout << "Congratulations you won" << endl;
                break;
            }
            else if (userin > 100)
            {
                cout << "Thats not even in range and you have wasted a turn" << endl;
            }
            else if (userin < 1)
            {
                cout << "Thats not even in range and you have wasted a turn" << endl;
            }
            else if (userin > snum && userin < 101)
            {
                cout << "Too high" << endl;
            }
            else if (userin < snum && userin > 0)
            {
                cout << "Too low" << endl;
            }
            if (i == maxg)
            {
                cout << "Sorry you are out of attempts. The random number was " << snum << endl;
            }
        }
        cout << "Would you like to play again (y/n): ";
        cin >> playmore;
        cout << endl;
    }
    cout << "Thanks for playing don't be shy to return" << endl;
}