#include "CircularWeapon.h"

CircularWeapon::CircularWeapon(float radius, float damages, int baseBulletNumber, float rotationSpeed, WeaponData weaponData, float attackRate) : Weapon(damages, attackRate, weaponData)
{
	_radius = radius;
	_rotationSpeed = rotationSpeed;
	_baseBulletNumber = baseBulletNumber;

	Bullet* bullet = new Bullet(sf::Color::Yellow, 10, { _position.x + 50, _position.y }, { 0, 0 }, 0, _damages);
	Bullet* bullet2 = new Bullet(sf::Color::Yellow, 10, { _position.x - 50, _position.y }, { 0, 0 }, 0, _damages);

	_bulletList.push_back(bullet);
	_bulletList.push_back(bullet2);
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

	for (Bullet* bullet : _bulletList) {
		bullet->SetPosition(sf::Vector2f(_position.x + (_radius * cos(_rotationAngle)), _position.y + (_radius * sin(_rotationAngle))));
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

