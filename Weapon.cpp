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
	std::cout << "Upgraded : " + _name << std::endl;
}
