#include "Weapon.h"

Weapon::Weapon(float damages, float attackRate)
{
	_damages = damages;
	_fireTimer = 0;
	_attackRate = attackRate;
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
}
