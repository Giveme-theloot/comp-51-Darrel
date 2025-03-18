#include <iostream>
using namespace std;
#include <ctime>
int shop(int &pscore)
{
    int shopping;
    while (true)
    {
        cout << "The Shop" << endl;
        cout << "1. Add +5 points (cost: 5 points)" << endl;
        cout << "2. Add +15 points (cost: 10 points)" << endl;
        cout << "3. Exit Shop" << endl;
        cout << "Enter your choice: ";
        cin >> shopping;

        if (shopping == 1)
        {
            if(pscore >= 5)
            {
                pscore -= 5;
                pscore += 5;
                cout << "+5 points will be added to your next round" << endl;
            }
            else
            {
                cout << "Not enough points brokie" << endl;
            }
        }
        else if (shopping == 2)
        {
            if (pscore >= 10)
            {
                pscore -= 10;
                pscore += 15;
                cout << "+15 points will be added to your next round" << endl;
            }
            else
            {
                cout << "Not enough points brokie" << endl; 
            }
        }
        else if (shopping == 3)
        {
            break;
        }
        else
        {
            cout << "Not enough points brokie" << endl;
        }
        cout << endl;
    }
    cout << endl;
    
}

int rolldi()
{
    return  rand() % 6 + 1;
}
void rollthedie(int &playscore, int &compscore, int &rounds, int &wins, int &losses, int &draws)
{
    int proll1 = rolldi();
    int proll2 = rolldi();
    int croll1 = rolldi();
    int croll2 = rolldi();

    int ptotal = proll1 + proll2;
    int ctotal = croll1 + croll2;
    rounds++;


    cout << "Round: " << rounds << " Gamble" << endl;
    cout << "Player rolled: " << proll1 << " + " << proll2 << " = " << ptotal << endl;
    cout << "Computer rolled: " << croll1 << " + " << croll2 << " = " << ctotal << endl;

    if (ptotal > ctotal)
    {
        cout << "Player wins this round. +20 points to player" << endl;
        playscore += 20;
        wins++;
    }
    else if (ptotal < ctotal)
    {
        cout << "Computer wins this round!!! +20 points to A.I" << endl;
        compscore += 20;
        losses++;
    }
    else
    {
        cout << "Its a Draw +10 points to both" << endl;
        playscore += 10; 
        compscore += 10;
        draws++;
    }
}


void stats(int rounds, int pscore, int cscore, int wins, int losses, int draws)
{
    cout << "Game Over" << endl;
    cout << "Rounds Played: " << rounds << endl;
    cout << "Players final score: " << pscore << endl;
    cout << "Computers final score: " << cscore << endl;
    while(true)
    {
        if (pscore > cscore)
        {
            cout << "Player wins the game." << endl;
        }
        else if (pscore < cscore)
        {
            cout << "Computer wins the game !!!" << endl;
        }
        else
        {
            cout << "It's a draw" << endl;
        }
        break;
    }
    
    cout << "Wins: " << wins << " | Draws: " << draws << " | Losses: " << losses << endl;
    
}
int main()
{
    srand(static_cast<unsigned int>(time(0)));
    char playmore = 'y';
    int playscore = 0;
    int compscore = 0;
    int rounds = 0;
    char shoping = 'y';
    int wins = 0;
    int draws = 0;
    int losses = 0;
    int score = 0;

    rolldi();

    cout << " Welcome to Dice the gambling game" << endl << "Do you wish to start gambling? (y/n): ";
    cin >> playmore;
    cout << endl;

    while (true)
    {
        cout << "Before continuing will you like to visit the shop (y/n): ";
        cin >> shoping;
        cout << endl;
        if (shoping == 'y' || shoping == 'Y')
        {
            shop(playscore);
        }
       
        rollthedie(playscore, compscore, rounds, wins, losses, draws);
        cout << "Again: (y/n): ";
        cin >> playmore;
        cout << endl;
        if(playmore == 'n' || playmore == 'N')
        {
            stats(rounds, playscore, compscore, wins, losses, draws);
            break;
        }
    }
    cout << "Thanks for Gambling";
}