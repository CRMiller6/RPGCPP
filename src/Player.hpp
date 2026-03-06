#pragma once

#include "Entity.hpp"
#include "Room.hpp"
#include "Dice.hpp"
#include <vector>

class Player : public Entity
{
public:
    void Start(Vec2 _pos);
    void Update();
    void AttackEnemy(Entity* enemy);

    int m_keyCount = 0;

private:
    int m_treasure = 0;
};