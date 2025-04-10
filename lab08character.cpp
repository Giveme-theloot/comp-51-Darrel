#include "lab08character.h"



Character::Character()
{
    name = " ";
    race = " ";
    sex = " ";

    playerrace = { "elf", "dwarf", "firelord", "goblin", "human"};

    level = 0, health = 0, totalhealth = 0, maxhealth = 0, heal = 0;
    level = 1, currentxp = 0, basexp = 83, xptolevel = basexp, minlevel = 1, maxlevel = 60;
}

void Character::charactercreation()
{
    int counter = 0;
    
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
    system("cls");
    for (int i = 0; i <= counter; i++)
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
            break;
        }
        Sleep(1000);
        system("cls");
        counter++;
    }
    name[0] = toupper(name[0]);
    sex[0] = toupper(sex[0]);
    race[0] = toupper(race[0]);
    totalhealth = health;
    maxhealth = totalhealth;
}