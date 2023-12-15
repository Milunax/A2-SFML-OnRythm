#include "Weapon.h"

WeaponData _pistol = {"Pistol"};
WeaponData _sword = { "Sword" };
WeaponData _garlic = { "Garlic" };
std::array<WeaponData, 3> _weaponDatabase = { _pistol, _sword, _garlic};

Weapon::Weapon(WeaponData weaponData) 
{
	_name = weaponData.Name;
}

std::string Weapon::GetName() 
{
	return _name;
}

void Weapon::UpgradeWeapon() 
{
	std::cout << "Upgraded : " + _name << std::endl;
}
