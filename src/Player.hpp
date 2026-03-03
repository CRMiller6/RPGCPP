#pragma once

#include "Entity.hpp"

class Player : public Entity
{
public:
    void Start(Vec2 _pos);
    void Update();
private:
    int m_keyCount = 0;
    int m_treasure = 0;
};