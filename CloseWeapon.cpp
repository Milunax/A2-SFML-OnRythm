#include "CloseWeapon.h"
#include "Math.h"

CloseWeapon::CloseWeapon(sf::Color color, float radius, float damages, float attackRate, WeaponData weaponData) : Weapon(damages, attackRate, weaponData)
{
	_color = color;
	_radius = radius;
}

void CloseWeapon::Update(RefsData data, Player* player)
{
	Weapon::Update(data, player);

	UpdateTimer(data);
}

void CloseWeapon::Draw(RefsData data)
{
	sf::CircleShape shape;
	shape.setOrigin(sf::Vector2f(_radius, _radius));
	shape.setRadius(_radius);
	shape.setFillColor(_color);
	shape.setPosition(_position);
	(*data.window).draw(shape);
}

void CloseWeapon::CheckCollision(std::vector<Enemy*>* enemyList)
{
	std::vector<Enemy*>::iterator enemyIt = enemyList->begin();
	CircleCollider weaponCol = { _position, _radius };

	std::vector<Enemy*> enemyToHit;

	while (enemyIt != enemyList->end())
	{
		CircleCollider enemyCol = (*enemyIt)->GetCollider();
		if (AreCircleCollidersOverlapping(weaponCol, enemyCol)) 
		{
			enemyToHit.push_back(*enemyIt);
		}
		enemyIt++;
	}

	if (_fireTimer > 1 / _attackRate) {
		for (Enemy* enemy : enemyToHit) 
		{
			enemy->TakeDamage(_damages);
		}
		_fireTimer = 0.0f;
	}
}

