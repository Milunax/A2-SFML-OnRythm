#include "CircularWeapon.h"

CircularWeapon::CircularWeapon(float radius, float damages, int baseBulletNumber, float rotationSpeed, WeaponData weaponData, float attackRate) : Weapon(damages, attackRate, weaponData)
{
	_radius = radius;
	_rotationSpeed = rotationSpeed;
	_baseBulletNumber = baseBulletNumber;

	Bullet* bullet = new Bullet(sf::Color::Yellow, 10, { _position.x + 50, _position.y }, { 0, 0 }, 0, _damages);

	_bulletList.push_back(bullet);
	_rotationAngle = 0.0f;
	_rotationSpeed = rotationSpeed;
}

void CircularWeapon::Draw(RefsData data)
{
	for (Bullet* bullet : _bulletList) {
		bullet->Draw(*data.window);
	}
}

void CircularWeapon::Update(RefsData data, Player* player)
{
	Weapon::Update(data, player);

	MoveBullets(data);
}

void CircularWeapon::MoveBullets(RefsData data)
{
	_rotationAngle += _rotationSpeed * data.deltaTime;
	float angleIncrement = 360.0f / (float)_bulletList.size();
	float bulletAngle = _rotationAngle;

	for (Bullet* bullet : _bulletList) {
		bullet->SetPosition(sf::Vector2f(_position.x + (_radius * cos(_rotationAngle)), _position.y + (_radius * sin(_rotationAngle))));
		bulletAngle += angleIncrement;
		//CheckCollision(data, bullet);
	}
}

void CircularWeapon::CheckCollision(std::vector<Enemy*>* enemyList)
{
	std::vector<Enemy*>::iterator enemyIt = enemyList->begin();


	while (enemyIt != enemyList->end())
	{
		CircleCollider enemyCol = (*enemyIt)->GetCollider();
		std::vector<Bullet*>::iterator bulletIt = _bulletList.begin();

		while (bulletIt != _bulletList.end())
		{
			CircleCollider bulletCol = (*bulletIt)->GetCollider();
			if (AreCircleCollidersOverlapping(bulletCol, enemyCol))
			{
				(*enemyIt)->TakeDamage((*bulletIt)->GetDamage());
				//sf::Text* text = CreateTextAtPosition((*data.window), (*enemyIt)->GetPosition(), (*data.baseFont), IntStringConcatenate((*bulletIt)->GetDamage(), ""), 24);
				//_uiManager->GetDamageTextList()->push_back(text);
			}
			bulletIt++;
		}
		enemyIt++;
	}
}

void CircularWeapon::ScaleStats()
{
	if (_level % 2 == 0) _rotationSpeed *= 1.61803398875f;
	if (_level % 3 == 0) _damages += 1.0f;
	if (_level % 5 == 0) _radius *= 1.35f;

}

