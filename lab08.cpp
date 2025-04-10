#include <iostream>
#include <string>
#include <windows.h>
#include <ctime>    
#include <cstdlib>
#include <algorithm>
using namespace std;

void hud();
void Combat();
void combathud();
void moving();
void createmonster();
void levelup();

string name = " ", race = " ", sex = " ";
int level = 0, xp = 0, health = 0, totalhealth = 0, maxhealth = 0, nextlevel = 0, heal = 0;
int currentxp = 0, basexp = 83, xptolevel = basexp, minlevel = 1, maxlevel = 60;
int monsterhp = 0;
int monsterxp = 0;
int monsterlevel = 0;
int counter = 3;
string monstername[] = {"Goblin", "Dwarf", "Orgre", "Witch", "Demon", "Wizard"};
int currentmonsternames = 5;
string currentmonstaer = " ";
string playerrace[] = {"elf", "dwarf", "firelord", "goblin", "human"};
int main()
{
    level = 1;
    xp = 0;
    nextlevel = 76;
    
    cout << "Enter character name: ";
    cin >> name;
    cout << "Enter Characters race\n";
    cout << "Elf\n";
    cout << "Dwarf\n";
    cout << "Firelord\n";
    cout << "Goblin\n";
    cout << "Human\n";
    cout << "Type your Race: ";
    cin >> race;
    for_each(race.begin(), race.end(), [](char & c){
        c = ::tolower(c);
    });

    for (int i = 0; i < sizeof(playerrace); i++)
    {
        if (race == "elf")
        {
            health = 80;
            break;
        }
        if (race == "dwarf")
        {
            health = 120;
            break;
        }
        if (race == "firelord")
        {
            health = 150;
            break;
        }
        if (race == "goblin")
        {
            health = 90;
            break;
        }
        if (race == "human")
        {
            health = 70;
            break;
        }
        else
        {
            health = 100;
            break;
        }
    }
    cout << "\n";
    cout << "Enter characters sex: ";
    cin >> sex;
    
    for (int i = 0; i < counter; i++)
    {
        if (i == 0)
        {
            cout << "Creating Avatar.\n";
        }
        if (i == 1)
        {
            cout << "Creating Avatar..\n";
        }
        if (i == 2)
        {
            cout << "Creating Avatar...\n";
        }
        Sleep(1000);
        system("cls");
    }
    name[0] = toupper(name[0]);
    sex[0] = toupper(sex[0]);
    race[0] = toupper(race[0]);
    totalhealth = health;
    maxhealth = totalhealth;

    hud();
    moving();
    //system("pause");
    return 0;
   
}

void hud()
{
    Sleep(500);
    system("cls");
    cout << "Name: " << name << "       Health: " << totalhealth << "\nRace: " << race << "\nSex: " << sex << "\nLevel: " << level << "\nexp: " << xp << "\nEXP to Level: " << nextlevel << endl;
    moving();
}

void combathud()
{
    Sleep(500);
    system("cls");
    cout << "Name: " << name << "       |       Monster Name: " << currentmonstaer << "\nHealth: " << totalhealth << "      |       Monster Health: " << monsterhp << "\nlevel: " << level << "     |       Monster Level: " << monsterlevel << endl;
}

void combat()
{
    combathud();
    int playerattack;
    int playerdamage = 8 * level / 2;
    //int playerdamage = 300000;
    int monsterattack = 6 * monsterlevel / 2;

    if (totalhealth >= 1 && monsterhp >= 1)
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
                totalhealth = totalhealth - monsterattack;
                cout << "You suffered " << monsterattack << " hp: " << totalhealth << endl;
                //change to function
                if (totalhealth <= 0)
                {
                    totalhealth = 0;
                    system("cls");
                    cout << "You dead cuh!\nYou were level: " << level << " you got wasted by a " << currentmonstaer << " mate!" << endl;
                    Sleep(2500);
                    exit(0);
                }
            }
            else if (monsterhp <= 0)
            {
                monsterhp = 0;
                levelup();
                cout << "\nYou defeated " << currentmonstaer << " you are rewarded with " << monsterxp << " xp.\nWell Done!\n";
                if (level != maxlevel)
                {
                    currentxp += monsterxp;
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
                heal = level * 10 / 2;
                cout << "You have been healed for " << heal << endl;
                totalhealth += heal;
                Sleep(1000);
                combat();
            }
            else
            {
                cout << "You failed to block the savage attack\n";
                totalhealth -= monsterattack;
                cout << "You were hit for " <<  monsterattack << " current hp " << totalhealth << endl;
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
                totalhealth -= monsterattack + 10;
                cout << "You suffered " << monsterattack + 10 << "Your current Health is " << totalhealth << endl;
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
        if (totalhealth <= 99)
        {
            totalhealth += 10 * level;
        }
        cout << "You healed by resting. Health is now: " << totalhealth << endl;
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
    xp = xp + monsterxp;

    if (xp >= nextlevel)
    {
        level++;
        nextlevel = nextlevel * 1.5;
        totalhealth = totalhealth + 20;
        maxhealth = totalhealth;
        cout << "LEVEL UP: " << level << endl;
        cout << "Health up cuh check it: " << totalhealth << endl;
        Sleep(2000);
        hud();
    }
}

void createmonster()
{
    monsterhp = 30;
    monsterlevel = (rand() % 3) + level;

    monsterhp = (rand() % 30) * monsterlevel; 

    monsterxp = monsterhp;

    if (monsterhp == 0)
        createmonster();
    if (monsterlevel == 0)
        createmonster();
}
