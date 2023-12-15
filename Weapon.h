#pragma once
#include <SFML/System/Vector2.hpp>
#include "RefsData.h"
#include "Player.h"
#include <iostream>
#include <array>

struct WeaponData {
    std::string Name;
};

extern WeaponData _pistol;
extern WeaponData _sword;
extern WeaponData _garlic;
extern std::array<WeaponData, 3> _weaponDatabase;

class Weapon {
    public:
        Weapon(float damages, float attackRate, WeaponData weaponData);
        virtual void Init(Player* player);
        virtual void Draw(RefsData data);
        virtual void Update();
        virtual void Attack();
        void UpgradeWeapon();
        std::string GetName();
    protected:
        std::string _name;
        float _fireTimer;
        float _attackRate;
        float _damages;
        sf::Vector2f _position;
        sf::Vector2f _orientationDirection;

        Player* _player;
};