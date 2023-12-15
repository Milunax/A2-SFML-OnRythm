#pragma once
#include <SFML/System/Vector2.hpp>
#include "RefsData.h"
#include "Player.h"

class Weapon {
    public:
        Weapon(float damages, float attackRate);
        virtual void Init(Player* player);
        virtual void Draw(RefsData data);
        virtual void Update();
        virtual void Attack();
    protected:
        float _fireTimer;
        float _attackRate;
        float _damages;
        sf::Vector2f _position;
        sf::Vector2f _orientationDirection;

        Player* _player;
};