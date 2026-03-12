#include "Room.hpp"

#include "Player.hpp"
#include "Goblin.hpp"
#include "Slime.hpp"

#include <fstream>
#include <string>
#include <random>

void Room::Load(std::string _path)
{
    m_monsters.clear();
    m_map.clear();
    m_doors.clear();

    std::ifstream file;
    file.open(_path);

    if (!file.is_open())
    {
        printf("file not found at: %s \n", _path.c_str());
        exit(1);
    }

    std::string word;
    int number;

    while (file >> word)
    {
        if (word == "level")
        {
            if (file >> number)
            {
                printf("open level: %i\n", number);
            }
        }

        if (word == "next_level")
        {
            if (file >> word)
            {
                m_doors.push_back(Door());
                m_doors[m_doors.size() - 1].path = word;
            }
        }

        if (word == "map")
        {
            m_map.push_back(std::vector<char>());
            while(file >> word)
            {
                if (word == "-2")
                {
                    break;
                }

                if (word == "-1")
                {
                    m_map.push_back(std::vector<char>());
                    continue;
                }

                if (word == "0")
                    m_map[m_map.size() - 1].push_back(' ');
                else
                    m_map[m_map.size() - 1].push_back(word[0]);
                
            }
        }
    }

    int doorCount = 0;
    for (int y = 0; y < m_map.size(); y++)
    {
        for (int x = 0; x < m_map[y].size(); x++)
        {
            if (m_map[y][x] == 'S')
                {
                    if (m_player == nullptr)
                    {
                        m_player = new Player();
                        m_player->Start(Vec2(x,y));
                    }
                    else
                    {
                        // just move player to spawn instead of making a new player
                        m_player->SetPosition(Vec2(x,y));
                    }

                    m_map[y][x] = ' ';
                }

            if (m_map[y][x] == 'D' || m_map[y][x] == 'L')
            {
                if (m_doors.size() - 1 >= doorCount)
                {
                    m_doors[doorCount].pos.x = x;
                    m_doors[doorCount].pos.y = y;
                    doorCount++;
                }
            }
            if (m_map[y][x] == 'G') {
                Monster* goblin = new Goblin();
                goblin->Start(Vec2(x, y));
                goblin->room = this;
                m_monsters.push_back(goblin);
                m_map[y][x] = ' ';
            }

            if (m_map[y][x] == 'O') {
                Monster* slime = new Slime();
                slime->Start(Vec2(x, y));
                slime->room = this;
                m_monsters.push_back(slime);
                m_map[y][x] = ' ';
            }
        }
    }
        // Heal a little when entering a room
    if (m_player)
    {
        int healChance = random_int(1, 100); // 1–100%
        if (healChance <= 50) { // 50% chance to heal
            int healAmount = random_int(1, 3); // heal 1–3 HP
            m_player->stats.HP += healAmount;
            if (m_player->stats.HP > m_player->stats.maxHP)
                m_player->stats.HP = m_player->stats.maxHP;

            m_healMessage = "You feel refreshed and recover " + std::to_string(healAmount) + " HP!";
        } else {
            m_healMessage = "";
        }
}
}

void Room::Update()
{
    system("cls");
    Draw();
    PrintRoomStatus();
    if (!m_healMessage.empty()) {
        std::cout << "\n" << m_healMessage << "\n";
        m_healMessage = ""; // clear after showing
    }
    if (m_player != nullptr)
    {
        m_player->room = this;
        m_player->Update();
    }
}

void Room::PrintRoomStatus() {
    if (m_player) {
        std::cout << "\n" << m_player->stats.name 
                  << " HP: " << m_player->stats.HP << "/" << m_player->stats.maxHP
                  << " | Coins: " << m_player->stats.coins << "\n";
    }

    /*
    for (Monster* m : m_monsters) {
        if (!m->IsDead()) {
            std::cout << m->stats.name 
                      << " HP: " << m->stats.HP << "/" << m->stats.maxHP 
                      << "\n";
        }
    }*/
}

void Room::Draw()
{
    for (int y = 0; y < m_map.size(); y++)
    {
        for (int x = 0; x < m_map[y].size(); x++)
        {
            printf("%c ", GetLocation(Vec2(x, y)));
        }
        printf("\n");
    }
    /*
    for (Monster* m : m_monsters)
        if (!m->IsDead())
            std::cout << m->stats.name << " HP: " << m->stats.HP << "/" << m->stats.maxHP << "\n";*/
}

char Room::GetLocation(Vec2 _pos)
{
    if (_pos.y >= m_map.size())
        return ' ';
    
    for (Monster* m : m_monsters)
        if (!m->IsDead() && m->GetPosition() == _pos)
            return m->Draw();

    if (_pos.x >= m_map[_pos.y].size())
        return ' ';

    if (m_player != nullptr)
        if (m_player->GetPosition() == _pos)
            return m_player->Draw();
    
    return m_map[_pos.y][_pos.x];
}

void Room::ClearLocation(Vec2 _pos)
{
    if (_pos.y >= m_map.size())
        return;
    
    if (_pos.x >= m_map[_pos.y].size())
        return;
    
    m_map[_pos.y][_pos.x] = ' ';
}

/*void Room::UnlockDoor(Vec2 _pos)
{
    m_map[_pos.y][_pos.x] = 'D';
} */

void Room::OpenDoor(Vec2 _pos)
{
    if (m_doors.empty())
        return;

    // checks if you have a key so you cant go to treasure room without one
    /*
    int r;
    std::string next;

    do {
        r = random_int(0, m_doors.size() - 1);
        next = m_doors[r].path;
    } while (next == "assets/treasure.map" && m_player->m_keyCount == 0);

    Load(next);
    */

    // temporary version without key check to allow testing of all rooms
    int r = random_int(0, m_doors.size() - 1);
    Load(m_doors[r].path);
}

void Room::CheckRoomCleared(){
    bool monstersRemaining = false;

    for (Monster* m : m_monsters) {
        if (!m->IsDead()) {
            monstersRemaining = true;
            break;
        }
    }

    if (!monstersRemaining) {
        std::cout << "\nThe Last Enemy Falls. You hear the doors unlock.";
        for (int y = 0; y < m_map.size(); y++) {
            for (int x=0; x < m_map[y].size(); x++){
                if (m_map[y][x] == 'L'){
                    m_map[y][x] = 'D'; 
                }
            }

        }
    }
}