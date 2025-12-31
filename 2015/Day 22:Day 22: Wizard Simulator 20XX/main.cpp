#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>

using namespace std;

// --- CONFIGURATION ---
// REPLACE with your puzzle input
const int BOSS_START_HP = 51;
const int BOSS_DAMAGE = 9;
const bool HARD_MODE = true; // Set to true for Part 2

// Spell Constants
const int COST_MISSILE = 53;
const int COST_DRAIN = 73;
const int COST_SHIELD = 113;
const int COST_POISON = 173;
const int COST_RECHARGE = 229;

enum SpellType { MISSILE, DRAIN, SHIELD, POISON, RECHARGE };

string getSpellName(int s) {
    switch(s) {
        case MISSILE: return "Magic Missile";
        case DRAIN: return "Drain";
        case SHIELD: return "Shield";
        case POISON: return "Poison";
        case RECHARGE: return "Recharge";
        default: return "Unknown";
    }
}

// --- GAME STATE ---
struct State {
    int mana_spent;
    int player_hp;
    int player_mana;
    int boss_hp;
    
    int shield_timer;
    int poison_timer;
    int recharge_timer;
    
    bool player_turn;
    
    // HISTORY: Keeps track of the sequence of spells used to reach this state
    vector<int> history; 

    // Priority Queue sorts by lowest mana spent
    bool operator>(const State& other) const {
        return mana_spent > other.mana_spent;
    }
};

// --- REPLAY FUNCTION ---
// Takes the winning sequence of spells and prints the battle details
void replayBattle(const vector<int>& spells) {
    int p_hp = 50;
    int p_mana = 500;
    int b_hp = BOSS_START_HP;
    int shield = 0, poison = 0, recharge = 0;
    
    int spell_idx = 0;
    
    cout << "\n=== BATTLE LOG ===" << endl;
    
    while (true) {
        // --- PLAYER TURN ---
        cout << "\n-- Player Turn --" << endl;
        cout << "- Player has " << p_hp << " HP, " << (shield>0?7:0) << " Armor, " << p_mana << " Mana" << endl;
        cout << "- Boss has " << b_hp << " HP" << endl;

        if (HARD_MODE) {
            p_hp--;
            cout << "Hard mode: Player loses 1 HP." << endl;
            if (p_hp <= 0) { cout << "Player died from exhaustion!" << endl; return; }
        }

        // Apply Effects
        if (shield > 0) { shield--; cout << "Shield is active; timer is now " << shield << endl; }
        else if (shield == 0) cout << "Shield wears off." << endl;
        
        if (poison > 0) { 
            b_hp -= 3; poison--; 
            cout << "Poison deals 3 damage; timer is now " << poison << endl; 
        }
        
        if (recharge > 0) { 
            p_mana += 101; recharge--; 
            cout << "Recharge provides 101 mana; timer is now " << recharge << endl; 
        }

        // Check Victory after effects
        if (b_hp <= 0) { cout << "*** Boss died from Poison! PLAYER WINS! ***" << endl; return; }

        // Cast Spell
        if (spell_idx >= spells.size()) {
            cout << "Error: Run out of recorded spells, but battle isn't over." << endl;
            return;
        }
        
        int spell = spells[spell_idx++];
        cout << "Player casts " << getSpellName(spell) << "." << endl;

        if (spell == MISSILE) { p_mana -= COST_MISSILE; b_hp -= 4; }
        else if (spell == DRAIN) { p_mana -= COST_DRAIN; b_hp -= 2; p_hp += 2; }
        else if (spell == SHIELD) { p_mana -= COST_SHIELD; shield = 6; }
        else if (spell == POISON) { p_mana -= COST_POISON; poison = 6; }
        else if (spell == RECHARGE) { p_mana -= COST_RECHARGE; recharge = 5; }

        if (b_hp <= 0) { cout << "*** Boss killed by spell! PLAYER WINS! ***" << endl; return; }

        // --- BOSS TURN ---
        cout << "\n-- Boss Turn --" << endl;
        cout << "- Player has " << p_hp << " HP, " << (shield>0?7:0) << " Armor, " << p_mana << " Mana" << endl;
        cout << "- Boss has " << b_hp << " HP" << endl;

        // Apply Effects
        int armor = 0;
        if (shield > 0) { armor = 7; shield--; cout << "Shield is active; timer is now " << shield << endl; }
        else if (shield == 0) cout << "Shield wears off." << endl;
        
        if (poison > 0) { 
            b_hp -= 3; poison--; 
            cout << "Poison deals 3 damage; timer is now " << poison << endl; 
        }
        
        if (recharge > 0) { 
            p_mana += 101; recharge--; 
            cout << "Recharge provides 101 mana; timer is now " << recharge << endl; 
        }

        // Check Victory after effects
        if (b_hp <= 0) { cout << "*** Boss died from Poison! PLAYER WINS! ***" << endl; return; }

        // Attack
        int dmg = max(1, BOSS_DAMAGE - armor);
        p_hp -= dmg;
        cout << "Boss attacks for " << BOSS_DAMAGE << " - " << armor << " = " << dmg << " damage!" << endl;

        if (p_hp <= 0) { cout << "Player died!" << endl; return; }
    }
}

// --- SOLVER ---
void solve() {
    priority_queue<State, vector<State>, greater<State>> pq;
    pq.push({0, 50, 500, BOSS_START_HP, 0, 0, 0, true, {}});

    int min_mana = 2147483647;
    vector<int> winning_history;

    while (!pq.empty()) {
        State cur = pq.top();
        pq.pop();

        if (cur.mana_spent >= min_mana) continue;

        // Hard Mode check
        if (HARD_MODE && cur.player_turn) {
            cur.player_hp--;
            if (cur.player_hp <= 0) continue;
        }

        // Apply Effects (Shield, Poison, Recharge)
        int armor = 0;
        if (cur.shield_timer > 0) { armor = 7; cur.shield_timer--; }
        if (cur.poison_timer > 0) { cur.boss_hp -= 3; cur.poison_timer--; }
        if (cur.recharge_timer > 0) { cur.player_mana += 101; cur.recharge_timer--; }

        // Check Boss Death from Effects
        if (cur.boss_hp <= 0) {
            if (cur.mana_spent < min_mana) {
                min_mana = cur.mana_spent;
                winning_history = cur.history;
            }
            continue;
        }

        if (cur.player_turn) {
            // Try casting all spells
            // 1. Magic Missile
            if (cur.player_mana >= COST_MISSILE) {
                State next = cur;
                next.player_mana -= COST_MISSILE;
                next.mana_spent += COST_MISSILE;
                next.boss_hp -= 4;
                next.history.push_back(MISSILE);
                next.player_turn = false;
                if (next.boss_hp <= 0) {
                    if (next.mana_spent < min_mana) {
                        min_mana = next.mana_spent;
                        winning_history = next.history;
                    }
                } else pq.push(next);
            }
            // 2. Drain
            if (cur.player_mana >= COST_DRAIN) {
                State next = cur;
                next.player_mana -= COST_DRAIN;
                next.mana_spent += COST_DRAIN;
                next.boss_hp -= 2;
                next.player_hp += 2;
                next.history.push_back(DRAIN);
                next.player_turn = false;
                if (next.boss_hp <= 0) {
                    if (next.mana_spent < min_mana) {
                        min_mana = next.mana_spent;
                        winning_history = next.history;
                    }
                } else pq.push(next);
            }
            // 3. Shield
            if (cur.player_mana >= COST_SHIELD && cur.shield_timer == 0) {
                State next = cur;
                next.player_mana -= COST_SHIELD;
                next.mana_spent += COST_SHIELD;
                next.shield_timer = 6;
                next.history.push_back(SHIELD);
                next.player_turn = false;
                pq.push(next);
            }
            // 4. Poison
            if (cur.player_mana >= COST_POISON && cur.poison_timer == 0) {
                State next = cur;
                next.player_mana -= COST_POISON;
                next.mana_spent += COST_POISON;
                next.poison_timer = 6;
                next.history.push_back(POISON);
                next.player_turn = false;
                pq.push(next);
            }
            // 5. Recharge
            if (cur.player_mana >= COST_RECHARGE && cur.recharge_timer == 0) {
                State next = cur;
                next.player_mana -= COST_RECHARGE;
                next.mana_spent += COST_RECHARGE;
                next.recharge_timer = 5;
                next.history.push_back(RECHARGE);
                next.player_turn = false;
                pq.push(next);
            }
        } else {
            // Boss Turn
            int dmg = max(1, BOSS_DAMAGE - armor);
            cur.player_hp -= dmg;
            cur.player_turn = true;
            if (cur.player_hp > 0) pq.push(cur);
        }
    }

    cout << "Calculation complete." << endl;
    cout << "Minimum Mana: " << min_mana << endl;
    
    // Now replay the events to show the user what happened
    replayBattle(winning_history);
}

int main() {
    solve();
    return 0;
}