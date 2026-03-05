#pragma once
#include "fogpi/Math.hpp"
#include <iostream>
#include <string>

struct Stats
{
    std::string name = "Unknown";
    int maxHP = 10;
    int HP = 10;
    int AC = 10;
    int attackBonus = 0;
    int DiceAmount = 1;
    int DiceSides = 6;
    int coins = 0;
};

class Room; // forward declaration

class Entity {
public:
    virtual ~Entity() {}
    
    void SetPosition(Vec2 _pos) { m_position = _pos; }
    
    Room* room = nullptr;

    virtual void Start(Vec2 _pos) {}  // base Start

    virtual void Update() {}

    Vec2 GetPosition() { return m_position; }
    char Draw() { return m_character; }

    Stats stats;

    void TakeDamage(int damage) {
        stats.HP -= damage;
        if (stats.HP < 0) stats.HP = 0;
    }

    bool IsDead() { return stats.HP <= 0; }

    void PrintStats() {
        std::cout << stats.name << " | HP: " << stats.HP << "/" << stats.maxHP;
    }

protected:
    Vec2 m_position;
    char m_character;
};