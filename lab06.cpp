#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int SIZE = 10;
const int EMPTY = 0;
const int SHIP = 1;
const int HIT = -1;
const int MISS = -2;
const int NUM_SHIPS = 6;
int shipSizes[NUM_SHIPS] = {2, 2, 3, 3, 5, 5}; 

void innitbfeild(int bfield[SIZE][SIZE])
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            bfield[i][j] = EMPTY;
        }
    }
}

bool canplaceship(int bfield[SIZE][SIZE], int row, int col, int length, bool horizon)
{
    if (horizon)
    {
        if (col + length > SIZE)
        {
            return false;
        }
        for (int i = 0; i < length; i++)
        {
            if (bfield[row][col + i] != EMPTY)
            {
                return false;
            }
        }
    }
    else
    {
        if(row + length > SIZE)
        {
            return false;
        }
        for (int i = 0; i < length; i++)
        {
            if (bfield[row + i][col] != EMPTY)
            {
                return false;
            }
        }
    }
    return true;
}

void placeship(int bfield[SIZE][SIZE], int row, int col, int length, bool horizon)
{
    if (horizon)
    {
        for (int i = 0; i <length; i++)
        {
            bfield[row][col + i] = SHIP;
        }
    }
    else
    {
        for (int i = 0; i < length; i++)
        {
            bfield[row + i][col] = SHIP;
        } 
    }  
}

void randplaceships(int bfield[SIZE][SIZE])
{
    srand(time(0));
    for (int  i = 0; i < NUM_SHIPS; i++)
    {
        int length = shipSizes[i];
        bool placed = false;
        while (!placed)
        {
            int row = rand() % SIZE;
            int col = rand() % SIZE;
            bool horizon = rand() % 2;
            if (canplaceship(bfield, row, col, length, horizon))
            {
                placeship(bfield, row, col, length, horizon);
                placed = true;
            }
        }
    }
}

void dispbfield(int bfield[SIZE][SIZE], bool revships = false)
{
    cout << "   ";
    for (int i = 0; i < SIZE; i++)
    {
        cout << i << " ";
    }
    cout << endl;

    for (int i = 0; i < SIZE; i++)
    {
        cout << i << "  ";
        for (int j = 0; j < SIZE; j++)
        {
            if(bfield[i][j] == HIT)
            {
                cout << "H ";
            }
            else if (bfield[i][j] == MISS)
            {
                cout << "M ";
            }
            else if (bfield[i][j] == SHIP && revships)
            {
                cout << "S ";
            }
            else
            {
                cout << "~ ";
            }
        }
        cout << endl;
    }
}

bool allshipsunk(int bfield[SIZE][SIZE])
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (bfield[i][j] == SHIP)
            {
                return false;
            }
        }
    }
    return true;
}

int main()
{
    cout << "Welcome to Battleship!\n";
    cout << "Enter coordinates to attack add a space between numbers (row and column between 0-9).\n";
    cout << "Enter -1 -1 to reveal all the ships on the grid.\n\n";
    int bfield[SIZE][SIZE];
    innitbfeild(bfield);
    randplaceships(bfield);
    
    while (true)
    {
        dispbfield(bfield);
        int row, col;
        cout << "Enter row and column: ";
        cin >> row >> col;

        if (row == -1 && col == -1)
        {
            cout << "\n[HACKS MODE ACTIVATED] Revealing all ahips:\n";
            dispbfield(bfield, true);
            continue;
        }
        
        if (row < 0 || row >= SIZE || col < 0 || col >= SIZE)
        {
            cout << "Invalid coordinates. Try again. \n";
            continue;
        }
        
        if (bfield[row][col] == SHIP)
        {
            bfield[row][col] = HIT;
            cout << "Miss!\n";
        }
        else if (bfield[row][col] == EMPTY)
        {
            bfield[row][col] = MISS;
            cout << "Miss!\n";
        }
        else
        {
            cout << "Already attacked that spot. Try again.\n";
            continue;
        }

        if(allshipsunk(bfield))
        {
            break;
        }
    }
    cout << "\nAll ships sunk! You win!\n";
    cout << "Final Battlefield:\n";
    dispbfield(bfield, true);
    return 0;
}