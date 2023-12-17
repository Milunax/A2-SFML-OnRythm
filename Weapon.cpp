#include "Weapon.h"
#include "Player.h"

WeaponData _range = {"Range"};
WeaponData _close = { "Close" };
WeaponData _book = { "Book" };
std::array<WeaponData, 3> _weaponDatabase = { _range, _close, _book};

Weapon::Weapon(float damages, float attackRate, WeaponData weaponData)
{
	_damages = damages;
	_fireTimer = 0;
	_attackRate = attackRate;
	_name = weaponData.Name;
}

void Weapon::Update(RefsData data, Player* player)
{
	_position = player->GetPosition();
	_orientationDirection = player->GetOrientationDirection();
	std::cout << _level << std::endl;
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
