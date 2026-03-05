#pragma once

#include <vector>
#include "Door.hpp"
#include "Monster.hpp"

class Entity;
class Player;

class Room {
public:
    void Load(std::string _path);
    void Draw();
    void Update();
    char GetLocation(Vec2 _pos);
    void ClearLocation(Vec2 _pos);
    void OpenDoor(Vec2 _pos);

    const std::vector<Monster*>& GetMonsters() const { return m_monsters; }

    void PrintRoomStatus();
private:
    std::vector<Entity*> m_entities;
    Player* m_player = nullptr;
    std::vector<Monster*> m_monsters; // full type now known
    std::vector<std::vector<char>> m_map;
    std::vector<Door> m_doors;
    std::string m_healMessage;
};
