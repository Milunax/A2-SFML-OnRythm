#pragma once
#include <SFML/System/Vector2.hpp>
#include "RefsData.h"
#include <iostream>
#include <array>
#include <vector>
#include "Enemy.h"

class Player;

struct WeaponData {
    std::string Name;
};

extern WeaponData _pistol;
extern WeaponData _area;
extern WeaponData _graviton;
extern std::array<WeaponData, 3> _weaponDatabase;

class Weapon 
{
    public:
        Weapon(float damages, float attackRate, WeaponData weaponData);
        virtual void Update(RefsData data, Player* player);
        virtual void CheckCollision(std::vector<Enemy*>* enemyList) = 0;
        virtual void Draw(RefsData data);
        void UpdateTimer(RefsData data);
        virtual void Attack();
        virtual void UpgradeWeapon();
        virtual void ScaleStats();
        std::string GetName();
    protected:
        std::string _name;
        int _level;
        float _fireTimer;
        float _attackRate;
        float _damages;
        sf::Vector2f _position;
        sf::Vector2f _orientationDirection;
};