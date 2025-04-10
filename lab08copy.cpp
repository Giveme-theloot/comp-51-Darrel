#include "lab08character.h"

void hud();
void combat();
void combathud();
void moving();
void createmonster();
void levelup();
//g++ lab08copy.cpp lab08character.cpp -o rpggame

int monsterhp = 0;
int monsterxp = 0;
int monsterlevel = 0;
int counter = 0;
string monstername[] = {"Goblin", "Dwarf", "Orgre", "Witch", "Demon", "Wizard"};
int currentmonsternames = 5;
string currentmonstaer = " ";

Character character;

int main()
{
    character.charactercreation();

    hud();
    moving();
    //system("pause");
    return 0;
   
}

void hud()
{
    Sleep(500);
    system("cls");
    cout << "Name: " << character.name << "       Health: " << character.totalhealth << "\nRace: " << character.race << "\nSex: " << character.sex << "\nLevel: " << character.level << "\nexp: " << character.currentxp << "\nEXP to Level: " << character.xptolevel << endl;
    moving();
}

void combathud()
{
    Sleep(500);
    system("cls");
    cout << "Name: " << character.name << "       |       Monster Name: " << currentmonstaer << "\nHealth: " << character.totalhealth << "      |       Monster Health: " << monsterhp << "\nlevel: " << character.level << "     |       Monster Level: " << monsterlevel << endl;
}

void combat()
{
    combathud();
    int playerattack;
    int playerdamage = 8 * character.level / 2;
    //int playerdamage = 300000;
    int monsterattack = 6 * monsterlevel / 2;

    if (character.totalhealth >= 1 && monsterhp >= 1)
    {
        cout << "\n";
        cout << "1. Attack\n";
        cout << "2. Block\n";
        cout << "3. RUN!\n";
        cout << "\n";
        cin >> playerattack;

        if (playerattack == 1)
        {
            cout << "Attacking... you did " << playerdamage << " to the " << currentmonstaer << endl;
            monsterhp = monsterhp - playerdamage;
            Sleep(1000);
            combathud();
            if (monsterhp >= 1)
            {
                cout << "\n";
                cout << "Monster is Attacking...\n";
                character.totalhealth = character.totalhealth - monsterattack;
                cout << "You suffered " << monsterattack << " hp: " << character.totalhealth << endl;
                //change to function
                if (character.totalhealth <= 0)
                {
                    character.totalhealth = 0;
                    system("cls");
                    cout << "You dead cuh!\nYou were level: " << character.level << " you got wasted by a " << currentmonstaer << " mate!" << endl;
                    Sleep(2500);
                    exit(0);
                }
            }
            else if (monsterhp <= 0)
            {
                monsterhp = 0;
                cout << "\nYou defeated " << currentmonstaer << " you are rewarded with " << monsterxp << " xp.\nWell Done!\n";

                if (character.level != character.maxlevel)
                {
                    character.currentxp += monsterxp;
                    levelup();
                }
                
                Sleep(1000);
                hud();
            }
            Sleep(1000);
            combat();
        }
        else if (playerattack == 2)
        {
            cout << "Blocking\n";
            int i = rand() % 100 + 1;
            if (i >= 50)
            {
                cout << "You Blocked the incoming attack\n";
                character.heal = character.level * 10 / 2;
                cout << "You have been healed for " << character.heal << endl;
                character.totalhealth += character.heal;
                Sleep(1000);
                combat();
            }
            else
            {
                cout << "You failed to block the savage attack\n";
                character.totalhealth -= monsterattack;
                cout << "You were hit for " <<  monsterattack << " current hp " << character.totalhealth << endl;
                Sleep(1000);
                combat();
            }
        }
        else if (playerattack == 3)
        {
            cout << "You are now attempting to run\n";
            int x = rand() % 100 + 1;
            if (x >= 50)
            {
                cout << "You ran away\n";
                hud();
            }
            else
            {
                cout << "You failed to escape\n";
                cout << "Monster does a savage attack on you!\n";
                character.totalhealth -= monsterattack + 10;
                cout << "You suffered " << monsterattack + 10 << "Your current Health is " << character.totalhealth << endl;
                Sleep(1000);
                combat();
            }
        }
        else
        {
            cout << "Invalid choice\n";
            Sleep(500);
            combat();
        }
    }
}

void moving()
{
    int choices;
    cout << "\n\n";
    cout << "1. Move Forward\n";
    cout << "2. Relax\n";
    cout << "3. Move Backwards\n";
    cout << "\n";
    cin >> choices;
    if (choices == 1)
    {
        int temp = rand() % 100 + 1;
        cout << "You begin moving forward...\n";
        if (temp >= 50)
        {
            createmonster();
            string tempname = monstername[rand() % currentmonsternames];
            cout << "A " << tempname << "! Prepare ro fight\n";
            currentmonstaer = tempname;
            Sleep(1000);
            combat();
        }
        cout << "You found nothing of interest\n";
        Sleep(1000);
        hud();
    }
    else if (choices == 2)
    {
        cout << "You want to set up camp for the evening\n";
        if (character.totalhealth <= 99)
        {
            character.totalhealth += 10 * character.level;
        }
        cout << "You healed by resting. Health is now: " << character.totalhealth << endl;
    }
    else if (choices == 3)
    {
        int temp = rand() % 100 + 1;
        cout << "You begin moving backwards...\n";
        if (temp >= 50)
        {
            createmonster();
            string tempname = monstername[rand() % currentmonsternames];
            cout << "A " << tempname << "! Prepare ro fight\n";
            currentmonstaer = tempname;
            Sleep(1000);
            combat();
        }
        cout << "You found nothing of interest\n";
        Sleep(1000);
        hud();
    }
    else
    {
        cout << "Inavlid choice\n";
        Sleep(500);
        moving();
    }
}

void levelup()
{
    if (character.currentxp >= character.xptolevel)
    {
        character.xptolevel += floor(character.level + 25 * pow(2, character.level / 7));
        character.totalhealth = floor(character.totalhealth + 13 * pow(2, character.level / 8));
        
        if (character.level >=  character.minlevel && character.level <= character.maxlevel)
        {
            character.level++;
        }
        else
        {
            character.level = 60;
        }
        character.maxhealth = character.totalhealth;
        cout << "LEVEL UP: " << character.level << endl;
        cout << "Health up cuh check it: " << character.totalhealth << endl;
        cout << "\n";
        Sleep(1000);
        levelup();
    }
    
    Sleep(2000);
    hud();
}

void createmonster()
{
    monsterhp = 30;
    monsterlevel = (rand() % 3) + character.level;

    monsterhp = (rand() % 30) * monsterlevel; 

    monsterxp = monsterhp;

    if (monsterhp == 0)
        createmonster();
    if (monsterlevel == 0)
        createmonster();
}