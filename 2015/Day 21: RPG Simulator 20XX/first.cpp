#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <string>

struct Item {
    std::string name;
    int cost;
    int damage;
    int armor;
};

struct Character {
    int hp;
    int damage;
    int armor;
};

// --- Shop Inventory ---
const std::vector<Item> WEAPONS = {
    {"Dagger", 8, 4, 0},
    {"Shortsword", 10, 5, 0},
    {"Warhammer", 25, 6, 0},
    {"Longsword", 40, 7, 0},
    {"Greataxe", 74, 8, 0}
};

const std::vector<Item> ARMOR = {
    {"No Armor", 0, 0, 0}, 
    {"Leather", 13, 0, 1},
    {"Chainmail", 31, 0, 2},
    {"Splintmail", 53, 0, 3},
    {"Bandedmail", 75, 0, 4},
    {"Platemail", 102, 0, 5}
};

const std::vector<Item> RINGS = {
    {"No Ring 1", 0, 0, 0}, 
    {"No Ring 2", 0, 0, 0}, 
    {"Damage +1", 25, 1, 0},
    {"Damage +2", 50, 2, 0},
    {"Damage +3", 100, 3, 0},
    {"Defense +1", 20, 0, 1},
    {"Defense +2", 40, 0, 2},
    {"Defense +3", 80, 0, 3}
};

bool fight(Character player, Character boss) {
    int playerDmg = std::max(1, player.damage - boss.armor);
    int bossDmg = std::max(1, boss.damage - player.armor);

    int turnsToKillBoss = (boss.hp + playerDmg - 1) / playerDmg;
    int turnsToKillPlayer = (player.hp + bossDmg - 1) / bossDmg;

    return turnsToKillBoss <= turnsToKillPlayer;
}

int main() {
    // --- INPUT: Replace with your specific puzzle input ---
    Character boss = {109, 8, 2}; 
    
    Character basePlayer = {100, 0, 0}; 

    int minGold = std::numeric_limits<int>::max();
    
    // Variables to store the best loadout found so far
    std::string bestWeapon, bestArmor, bestRing1, bestRing2;

    for (const auto& w : WEAPONS) {
        for (const auto& a : ARMOR) {
            for (size_t r1 = 0; r1 < RINGS.size(); ++r1) {
                for (size_t r2 = r1 + 1; r2 < RINGS.size(); ++r2) {
                    
                    int currentCost = w.cost + a.cost + RINGS[r1].cost + RINGS[r2].cost;
                    int currentDmg = w.damage + a.damage + RINGS[r1].damage + RINGS[r2].damage;
                    int currentArm = w.armor + a.armor + RINGS[r1].armor + RINGS[r2].armor;

                    Character equippedPlayer = basePlayer;
                    equippedPlayer.damage += currentDmg;
                    equippedPlayer.armor += currentArm;

                    if (fight(equippedPlayer, boss)) {
                        // If this loadout wins AND is cheaper than what we found before
                        if (currentCost < minGold) {
                            minGold = currentCost;
                            
                            // Save the names of the items
                            bestWeapon = w.name;
                            bestArmor = a.name;
                            bestRing1 = RINGS[r1].name;
                            bestRing2 = RINGS[r2].name;
                        }
                    }
                }
            }
        }
    }

    std::cout << "--- Winner Found! ---" << std::endl;
    std::cout << "Total Gold: " << minGold << std::endl;
    std::cout << "Weapon:     " << bestWeapon << std::endl;
    std::cout << "Armor:      " << bestArmor << std::endl;
    std::cout << "Ring 1:     " << bestRing1 << std::endl;
    std::cout << "Ring 2:     " << bestRing2 << std::endl;

    return 0;
}