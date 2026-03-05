#pragma once
#include "Monster.hpp"

// Goblin enemy
class Goblin : public Monster
{
public:
    void Start(Vec2 _pos) override {
        m_position = _pos;
        m_character = 'G';

        stats.name = "Goblin";
        stats.maxHP = 12;
        stats.HP = 12;
        stats.AC = 11;
        stats.attackBonus = 1;
        stats.DiceAmount = 1;
        stats.DiceSides = 6;
        stats.coins = 3;
    }
};