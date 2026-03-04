#include "Player.hpp"
#include "Room.hpp"
#include "fogpi/io.hpp"
#include <limits>
#include <iostream>



void Player::Start(Vec2 _pos) {
    m_character = 'P';
    m_position = _pos;
    stats.name = "Player";
    stats.maxHP = 20;
    stats.HP = 20;
    stats.AC = 12;
    stats.attackBonus = 2;
    stats.DiceAmount = 1;
    stats.DiceSides = 12;
    stats.coins = 0;
}

#include <iostream>
#include <limits>

void ClearInputBuffer() {
    // Flush everything up to and including the next newline
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void WaitForEnter() {
    std::cout << "";
    std::string dummy;
    std::getline(std::cin, dummy); // waits for the next Enter
}


// Player attack function
void Player::AttackEnemy(Entity* enemy) {
    int attackRoll = random_int(1, 20) + stats.attackBonus;
    std::cout << stats.name << " attacks " << enemy->stats.name 
              << "! Rolled " << attackRoll << " vs AC " << enemy->stats.AC << std::endl;
    WaitForEnter();

    if (attackRoll >= enemy->stats.AC) {
        std::vector<Die> dice;
        for (int i = 0; i < stats.DiceAmount; i++)
            dice.push_back({stats.DiceSides});

        RollStats dmg = RollDice(dice);
        enemy->TakeDamage(dmg.total);

        std::cout << "Hit! Dealt " << dmg.total << " damage." << std::endl;
    } else {
        std::cout << "Missed!" << std::endl;
    }
    WaitForEnter();

    enemy->PrintStats();
    WaitForEnter();
}

void Player::Update() {
    //while(request_char("hit w to continue: ") != 'w') {}

    char directionInput;

    do {
        directionInput = request_char("\nwasd and Enter to move");
    } while (directionInput != 'w' &&
             directionInput != 'a' &&
             directionInput != 's' &&
             directionInput != 'd');
    
    Vec2 direction(0.0f);

    switch (directionInput)
    {
    case 'w':
        direction = {0.0f, -1.0f};
        break;
    case 'a':
        direction = {-1.0f, 0.0f};
        break;
    case 's':
        direction = {0.0f, 1.0f};
        break;
    case 'd':
        direction = {1.0f, 0.0f};
        break;
    default:
        direction = {0.0f, 1.0f};
        break;
    }

    Vec2 tryPos = m_position + direction;

    // --- COMBAT CHECK ---
    Monster* targetEnemy = nullptr;
    for (Monster* m : room->GetMonsters())
        if (m->GetPosition() == tryPos && !m->IsDead())
            targetEnemy = m;

if (targetEnemy) {
    std::cout << "\nYou encounter a " << targetEnemy->stats.name << "!\n";
    WaitForEnter();

    // Player attacks once
    AttackEnemy(targetEnemy);

    // Monster retaliates if alive
    if (!targetEnemy->IsDead()) {
        int attackRoll = random_int(1, 20) + targetEnemy->stats.attackBonus;
        std::cout << targetEnemy->stats.name << " attacks you! Rolled "
                  << attackRoll << " vs AC " << stats.AC << std::endl;
        WaitForEnter();

        if (attackRoll >= stats.AC) {
            std::vector<Die> dice;
            for(int i = 0; i < targetEnemy->stats.DiceAmount; i++)
                dice.push_back({targetEnemy->stats.DiceSides});
            RollStats dmg = RollDice(dice);
            stats.HP -= dmg.total;
            std::cout << "You take " << dmg.total << " damage!\n";
        } else {
            std::cout << targetEnemy->stats.name << " missed!\n";
        }
        WaitForEnter();
    } else {
        // Monster defeated
        std::cout << targetEnemy->stats.name << " is defeated! You loot "
                  << targetEnemy->stats.coins << " coins.\n";
        stats.coins += targetEnemy->stats.coins;
        WaitForEnter();
    }

    // Print player stats after the round
    PrintStats();
    WaitForEnter();

    return; // Player doesn't move into enemy space
}
    if (room->GetLocation(tryPos) == 'K') {
        m_keyCount++;
        room->ClearLocation(tryPos);
    }

    if (room->GetLocation(tryPos) == 'T') {
        m_treasure++;
        room->ClearLocation(tryPos);
    }

    if (room->GetLocation(tryPos) == ' ') {
        m_position = tryPos;
    }

    if (room->GetLocation(tryPos) == 'D') {
        room->OpenDoor(tryPos);
    }

    
}

