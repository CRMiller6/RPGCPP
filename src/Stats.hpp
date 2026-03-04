#pragma once
#include <string>

// Stat block for player and enemy
struct Stats
{
    std::string name = "Unknown";
    int maxHP = 10;        // Maximum HP
    int HP = 10;
    int AC = 10;           // Armor Class (to-hit DC)
    int attackBonus = 0;   // Bonus added to D20 attack roll
    int DiceAmount = 1; // Number of dice for damage
    int DiceSides = 6;  // Sides of each damage dice
    int coins = 0;
};