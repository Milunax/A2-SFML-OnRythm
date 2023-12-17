#include "Weapon.h"
#include "Player.h"

WeaponData _pistol = {"Pistol"};
WeaponData _area = { "Area" };
WeaponData _graviton = { "Graviton" };
std::array<WeaponData, 3> _weaponDatabase = { _pistol, _area, _graviton };

Weapon::Weapon(float damages, float attackRate, WeaponData weaponData)
{
	_damages = damages;
	_fireTimer = 0;
	_attackRate = attackRate;
	_name = weaponData.Name;
	_level = 1;
}

void Weapon::Update(RefsData data, Player* player)
{
	_position = player->GetPosition();
	_orientationDirection = player->GetOrientationDirection();
}

void Weapon::Draw(RefsData data)
{
}


void Weapon::UpdateTimer(RefsData data)
{
	_fireTimer += data.deltaTime;
}

void Weapon::Attack()
{
}

std::string Weapon::GetName() 
{
	return _name;
}

void Weapon::UpgradeWeapon() 
{
	_level += 1;
	ScaleStats();
}

void Weapon::ScaleStats()
{
}
