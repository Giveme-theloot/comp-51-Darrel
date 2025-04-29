#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <algorithm>

using namespace std;

// Structures
struct Item {
    string name;
    string type; // Weapon, Armor, Heal
    int value;
};

struct Stats {
    int HP, MP, Strength, Defense, XP, level;
};

struct Character {
    string name;
    string charClass;
    Stats stats;
    vector<Item> inventory;
    Item equippedWeapon = {"None", "Weapon", 0};
    Item equippedArmor = {"None", "Armor", 0};
    int x, y;
    int healsLeft = 5;
    int monstersSlain = 0;
    bool hasActiveQuest = false;
    string questType; // "Slay" or "Riddle"
};

struct Enemy {
    string name;
    int HP, MP, strength, defense;
    bool isBoss = false;
    bool hasPhases = false;
};

// Globals
Character player;
bool inDungeon = false;

// Maps
const int MAP_WIDTH = 6;
const int MAP_HEIGHT = 5;

vector<vector<char>> worldMap = {
    {'E','E','M','B','E','M'},
    {' ','N','M','E','M','E'},
    {'M','M',' ',' ','E','N'},
    {'N',' ','P','M',' ','E'},
    {'M','E',' ','E','E','M'}
};

vector<vector<char>> dungeonMap = {
    {'M','M','M','E','B','M'},
    {' ',' ','M','E','M','E'},
    {'M','M','P',' ','E',' '},
    {'N',' ','P','M',' ','E'},
    {'M','E',' ','E','E','M'}
};

// Enemy list
vector<Enemy> enemyList = {
    {"Goblin", 20, 0, 5, 2},
    {"Skeleton", 25, 0, 7, 3},
    {"Orc", 35, 0, 10, 5},
    {"Dark Mage", 30, 10, 8, 4}
};

// Drop list
vector<Item> dropList = {
    {"Iron Sword", "Weapon", 5},
    {"Steel Dagger", "Weapon", 3},
    {"Leather Armor", "Armor", 4},
    {"Chainmail", "Armor", 6}
};

// Functions

void printMap() {
    vector<vector<char>>& currentMap = (inDungeon ? dungeonMap : worldMap);
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            if (i == player.y && j == player.x)
                cout << "\033[1;32mP\033[0m  ";  // Green for Player
            else if (currentMap[i][j] == 'M')
                cout << "\033[1;31mM\033[0m  ";  // Red for Monsters
            else if (currentMap[i][j] == 'B')
                cout << "\033[1;33mB\033[0m  ";  // Yellow for Bosses
            else if (currentMap[i][j] == 'N')
                cout << "\033[1;34mN\033[0m  ";  // Blue for NPCs
            else if (currentMap[i][j] == 'P')
                cout << "\033[1;36mP\033[0m  ";  // Cyan for Potions
            else
                cout << currentMap[i][j] << "  ";
        }
        cout << endl;
    }
}

void showInventory() {
    cout << "\nInventory:\n";
    for (size_t i = 0; i < player.inventory.size(); i++) {
        cout << i + 1 << ". " << player.inventory[i].name << " (" << player.inventory[i].type << " +" << player.inventory[i].value << ")\n";
    }
    cout << "\nEquipped Weapon: " << player.equippedWeapon.name << " (+" << player.equippedWeapon.value << ")\n";
    cout << "Equipped Armor: " << player.equippedArmor.name << " (+" << player.equippedArmor.value << ")\n";
}

void equipItem() {
    showInventory();
    cout << "\nChoose item number to equip: ";
    int num;
    cin >> num;
    if (num < 1 || num > player.inventory.size()) {
        cout << "Invalid choice.\n";
        return;
    }
    Item item = player.inventory[num - 1];
    if (item.type == "Weapon") {
        player.equippedWeapon = item;
        cout << "You equipped: " << item.name << "!\n";
    } else if (item.type == "Armor") {
        player.equippedArmor = item;
        cout << "You equipped: " << item.name << "!\n";
    } else {
        cout << "Cannot equip this item.\n";
    }
}

void saveGame() {
    ofstream file("savegame.txt");
    file << player.name << endl;
    file << player.charClass << endl;
    file << player.stats.HP << " " << player.stats.MP << " " << player.stats.Strength << " " << player.stats.Defense << " " << player.stats.XP << " " << player.stats.level << endl;
    file << player.x << " " << player.y << endl;
    file << player.equippedWeapon.name << " " << player.equippedWeapon.type << " " << player.equippedWeapon.value << endl;
    file << player.equippedArmor.name << " " << player.equippedArmor.type << " " << player.equippedArmor.value << endl;
    file << player.inventory.size() << endl;
    for (auto& item : player.inventory) {
        file << item.name << " " << item.type << " " << item.value << endl;
    }
    file.close();
    cout << "Game Saved!\n";
}

void loadGame() {
    ifstream file("savegame.txt");
    if (!file.is_open()) {
        cout << "No saved game found.\n";
        return;
    }
    int invSize;
    file >> ws;
    getline(file, player.name);
    getline(file, player.charClass);
    file >> player.stats.HP >> player.stats.MP >> player.stats.Strength >> player.stats.Defense >> player.stats.XP >> player.stats.level;
    file >> player.x >> player.y;
    file >> player.equippedWeapon.name >> player.equippedWeapon.type >> player.equippedWeapon.value;
    file >> player.equippedArmor.name >> player.equippedArmor.type >> player.equippedArmor.value;
    file >> invSize;
    player.inventory.clear();
    for (int i = 0; i < invSize; i++) {
        Item item;
        file >> item.name >> item.type >> item.value;
        player.inventory.push_back(item);
    }
    file.close();
    cout << "Game Loaded!\n";
}

void levelUp() {
    if (player.stats.XP >= 50) {
        player.stats.XP = 0;
        player.stats.level++;
        player.stats.HP += 20;
        player.stats.Strength += 5;
        player.stats.Defense += 3;
        cout << "\n*** You Leveled Up! (Level " << player.stats.level << ") ***\n";
    }
}

void giveDrop() {
    if (rand() % 100 < 70) { // 70% chance for a drop
        Item drop = dropList[rand() % dropList.size()];
        player.inventory.push_back(drop);
        cout << "You found a " << drop.name << "!\n";
    }
}

void giveLegendaryReward() {
    vector<Item> legendaryItems = {
        {"Drifter's Blade", "Weapon", 20},
        {"Drifter's Shield", "Armor", 20},
        {"Drifter's Mask", "Armor", 15}
    };
    Item reward = legendaryItems[rand() % legendaryItems.size()];
    player.inventory.push_back(reward);
    cout << "You received legendary item: " << reward.name << "!\n";
}

void combat(Enemy& enemy) {
    cout << "\nYou encountered a " << enemy.name << "!\n";
    player.healsLeft = 5;

    // Boss Phase Logic
    bool phaseChanged = false;
    while (enemy.HP > 0 && player.stats.HP > 0) {
        cout << "\nPlayer HP: " << player.stats.HP << " | Enemy HP: " << enemy.HP << endl;
        if (enemy.isBoss && !phaseChanged && enemy.HP <= enemy.HP / 2) {
            // Boss Transformation
            enemy.strength *= 1.5;
            enemy.defense *= 1.5;
            enemy.HP = enemy.HP * 1.5;
            enemy.hasPhases = true;
            phaseChanged = true;
            cout << enemy.name << " transforms into a stronger form!\n";
        }

        cout << "1. Attack  2. Skill  3. Heal (" << player.healsLeft << " left)  4. Dodge  5. Flee  6. Equip Item\n";
        int choice;
        cin >> choice;
        if (choice == 1) {
            int dmg = player.stats.Strength + player.equippedWeapon.value + rand() % 5;
            cout << "You deal " << dmg << " damage!\n";
            enemy.HP -= dmg;
        } else if (choice == 2) {
            int dmg = (player.stats.Strength + player.equippedWeapon.value) * 2;
            cout << "You unleash a skill! " << dmg << " damage!\n";
            player.stats.MP -= 5;
            enemy.HP -= dmg;
        } else if (choice == 3) {
            if (player.healsLeft > 0) {
                player.stats.HP += 20;
                player.healsLeft--;
                cout << "You heal for 20 HP!\n";
            } else {
                cout << "No heals left!\n";
            }
        } else if (choice == 4) {
            if (rand() % 100 < 65) {
                cout << "You tried to dodge but got hit!\n";
                int edmg = enemy.strength - player.stats.Defense - player.equippedArmor.value;
                player.stats.HP -= max(0, edmg + rand() % 5);
            } else {
                cout << "You dodged successfully! +10 HP recovered!\n";
                player.stats.HP += 10;
                continue;
            }
        } else if (choice == 5) {
            if (rand() % 2 == 0) {
                cout << "You fled successfully!\n";
                return;
            } else {
                cout << "Failed to flee!\n";
            }
        } else if (choice == 6) {
            equipItem();
            continue;
        }

        if (enemy.HP > 0) {
            int edmg = enemy.strength - player.stats.Defense - player.equippedArmor.value;
            edmg = max(0, edmg + rand() % 5);
            player.stats.HP -= edmg;
            cout << enemy.name << " hits you for " << edmg << "!\n";
        }
    }

    if (player.stats.HP <= 0) {
        cout << "You died. Game Over.\n";
        exit(0);
    }
    cout << "\nYou defeated the " << enemy.name << "!\n";
    player.stats.XP += 20;
    player.monstersSlain++;
    levelUp();
    giveDrop();
}

void npcQuest() {
    if (player.hasActiveQuest) {
        cout << "You already have a quest!\n";
        return;
    }
    cout << "NPC offers a quest:\n1. Slay 5 monsters\n2. Solve a riddle\n";
    int choice;
    cin >> choice;
    if (choice == 1) {
        player.hasActiveQuest = true;
        player.questType = "Slay";
        player.monstersSlain = 0;
        cout << "Quest accepted: Slay 5 monsters.\n";
    } else if (choice == 2) {
        cout << "Riddle: What has 4 legs in the morning, 2 in the afternoon, and 3 in the evening?\n";
        string answer;
        cin.ignore();
        getline(cin, answer);
        transform(answer.begin(), answer.end(), answer.begin(), ::tolower);
        if (answer == "human") {
            cout << "Correct!\n";
            giveLegendaryReward();
        } else {
            cout << "Wrong answer.\n";
        }
    } else {
        cout << "Quest declined.\n";
    }
}

void checkQuestProgress() {
    if (player.hasActiveQuest && player.questType == "Slay" && player.monstersSlain >= 5) {
        cout << "Quest completed!\n";
        player.hasActiveQuest = false;
        giveLegendaryReward();
    }
}

// --- Game Loop --- //
void explore() {
    vector<vector<char>>& currentMap = (inDungeon ? dungeonMap : worldMap);
    cout << "\nMove: (N)orth, (S)outh, (E)ast, (W)est\n";
    char dir;
    cin >> dir;
    if ((dir == 'N' || dir == 'n') && player.y > 0) player.y--;
    else if ((dir == 'S' || dir == 's') && player.y < MAP_HEIGHT-1) player.y++;
    else if ((dir == 'E' || dir == 'e') && player.x < MAP_WIDTH-1) player.x++;
    else if ((dir == 'W' || dir == 'w') && player.x > 0) player.x--;
    else cout << "Invalid move!\n";

    char tile = currentMap[player.y][player.x];
    if (tile == 'M') combat(enemyList[rand() % enemyList.size()]);
    else if (tile == 'B') {
        // Create the final boss object
        Enemy finalBoss = {"Final Boss", 60, 20, 15, 8, true};
        combat(finalBoss);  // Pass it to combat function
        if (!inDungeon) {
            inDungeon = true;
            player.x = 0;
            player.y = 0;
            cout << "You enter the Dungeon!\n";
        }
    }
    else if (tile == 'N') npcQuest();
    else if (tile == 'P') player.inventory.push_back({"Potion", "Heal", 10});
    else cout << "You find nothing of interest.\n";

    checkQuestProgress();
}

void newGame() {
    cout << "Enter your character name: ";
    getline(cin, player.name);
    cout << "Choose class (Warrior/Mage/Rogue): ";
    getline(cin, player.charClass);
    player.stats = {100, 30, 10, 5, 0, 1};
    player.x = 0; player.y = 0;
    player.inventory.push_back({"Potion", "Heal", 10});
    cout << "Game Started!\n";
}

void mainMenu() {
    srand(time(0));
    while (true) {
        cout << "\n--- DRIFTER ---\n";
        cout << "1. New Game\n2. Load Game\n3. Quit\n";
        int opt;
        cin >> opt;
        cin.ignore();
        if (opt == 1) { newGame(); break; }
        else if (opt == 2) { loadGame(); break; }
        else if (opt == 3) exit(0);
        else cout << "Invalid option.\n";
    }
}

int main() {
    mainMenu();
    cout << "There once was a great hero a long long time ago. He fought a hard battle alone which ended in his disappearance.\nGone frome the world we need a hero it save us once again and I elect you my DRIFTER" << endl;
    while (true) {
        cout << "\n1. Explore\n2. Show Map\n3. Inventory\n4. Save Game\n5. Equip Item\n6. Quit\n";
        int action;
        cin >> action;
        if (action == 1) explore();
        else if (action == 2) printMap();
        else if (action == 3) showInventory();
        else if (action == 4) saveGame();
        else if (action == 5) equipItem();
        else if (action == 6) break;
    }
    return 0;
}