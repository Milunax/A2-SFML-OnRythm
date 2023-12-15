#include "CloseWeapon.h"
#include "Math.h"

CloseWeapon::CloseWeapon(sf::Color color, float radius, float damages, float attackRate, WeaponData weaponData) : Weapon(damages, attackRate, weaponData)
{
	_color = color;
	_radius = radius;
}

void CloseWeapon::Update(RefsData data)
{
	UpdateTimer(data);
	if (_fireTimer > 1 / _attackRate) {
		CheckCollision(data);
		_fireTimer = 0.0f;
	}
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

void CloseWeapon::CheckCollision(RefsData data)
{
	/*std::vector<Enemy*>::iterator enemyIt = _enemyList->begin();
	CircleCollider weaponCol = { _position, _radius };

	while (enemyIt != _enemyList->end())
	{
		CircleCollider enemyCol = (*enemyIt)->GetCollider();
		if (AreCircleCollidersOverlapping(weaponCol, enemyCol)) 
		{
			(*enemyIt)->TakeDamage(_damages);
		}
		enemyIt++;
	}*/
}

