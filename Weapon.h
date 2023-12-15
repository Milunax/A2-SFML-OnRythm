#pragma once
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
        Weapon(WeaponData weaponData);
        void Draw();
        void UpgradeWeapon();
        std::string GetName();
    protected:
        std::string _name;
        float _fireRate;
        float _damages;
};