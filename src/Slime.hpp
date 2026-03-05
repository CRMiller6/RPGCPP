#pragma once
#include "Monster.hpp"

// Slime enemy
class Slime : public Monster
{
public:
    void Start(Vec2 _pos) override {
        m_position = _pos;
        m_character = 'O';

        stats.name = "Ooze";
        stats.maxHP = 12;
        stats.HP = 12;
        stats.AC = 5;
        stats.attackBonus = 0;
        stats.DiceAmount = 1;
        stats.DiceSides = 4;
        stats.coins = 2;
    }
};