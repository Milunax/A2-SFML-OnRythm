#include "CloseWeapon.h"
#include "Math.h"

CloseWeapon::CloseWeapon(sf::Color color, float radius, float damages, float attackRate, WeaponData weaponData) : Weapon(damages, attackRate, weaponData)
{
	_color = color;
	_radius = radius;
	_isTransparencyGoingDown = true;
	_transparency = 255;
}

void CloseWeapon::Update(RefsData data, Player* player)
{
	Weapon::Update(data, player);

	UpdateTimer(data);

	BlinkTransparency();
}

void CloseWeapon::Draw(RefsData data)
{
	sf::CircleShape shape;
	shape.setOrigin(sf::Vector2f(_radius, _radius));
	shape.setRadius(_radius);
	shape.setFillColor(sf::Color(_color.r, _color.g, _color.b, _transparency));
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

void CloseWeapon::ScaleStats()
{
	if (_level % 2 == 0) _radius *= 1.35f;
	if (_level % 3 == 0) _damages += 1.0f;
	if (_level % 5 == 0) _attackRate *= 2.0f;
}

void CloseWeapon::BlinkTransparency()
{
	if (_isTransparencyGoingDown) {
		_transparency = std::clamp(_transparency - 1, 0, 125);
		if (_transparency <= 0) {
			_isTransparencyGoingDown = false;
		}
	}
	else if (!_isTransparencyGoingDown) {
		_transparency = std::clamp(_transparency + 1, 0, 125);
		if (_transparency >= 125) {
			_isTransparencyGoingDown = true;
		}
	}
}

