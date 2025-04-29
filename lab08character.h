#pragma once

#include "lab08.h"
class Character
{
public:
    Character();
    
    string name, race, sex;
    vector<string> playerrace;
    int health, totalhealth, maxhealth, heal;
    int level, currentxp, basexp, xptolevel, minlevel, maxlevel;
    void charactercreation();
};