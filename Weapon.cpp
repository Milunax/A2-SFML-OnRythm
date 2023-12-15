#include "Weapon.h"

WeaponData _pistol = {"Pistol"};
WeaponData _sword = { "Sword" };
WeaponData _garlic = { "Garlic" };
std::array<WeaponData, 3> _weaponDatabase = { _pistol, _sword, _garlic};

Weapon::Weapon(float damages, float attackRate, WeaponData weaponData)
{
	_damages = damages;
	_fireTimer = 0;
	_attackRate = attackRate;
	_name = weaponData.Name;
}

void Weapon::Init(Player* player)
{
	_player = player;
}

void Weapon::Draw(RefsData data)
{
}

void Weapon::Update()
{
	_position = _player->GetPosition();
	_orientationDirection = _player->GetOrientationDirection();
}

void Weapon::Attack()
{

std::string Weapon::GetName() 
{
	return _name;
}

void Weapon::UpgradeWeapon() 
{
	std::cout << "Upgraded : " + _name << std::endl;
}
