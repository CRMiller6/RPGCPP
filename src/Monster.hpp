#pragma once
#include "Entity.hpp"

class Monster : public Entity {
public:
    virtual void Start(Vec2 _pos) override = 0;
};