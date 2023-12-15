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

void CircularWeapon::Update(RefsData data)
{
	MoveBullets(data);
}

void CircularWeapon::MoveBullets(RefsData data)
{
	_rotationAngle += _rotationAngle * data.deltaTime;

	for (Bullet* bullet : _bulletList) {
		bullet->SetPosition(sf::Vector2f(_position.x + (_radius * cos(_rotationAngle)), _position.y + (_radius * sin(_rotationAngle))));
		CheckCollision(data, bullet);
	}
}

void CircularWeapon::CheckCollision(RefsData data, Bullet* bullet)
{
	//std::vector<Enemy*>::iterator enemyIt = _enemyList->begin();


	//while (enemyIt != _enemyList->end())
	//{
	//	CircleCollider enemyCol = (*enemyIt)->GetCollider();
	//	CircleCollider bulletCol = bullet->GetCollider();
	//	if (AreCircleCollidersOverlapping(bulletCol, enemyCol))
	//	{
	//		(*enemyIt)->TakeDamage(_damages);
	//		sf::Text* text = CreateTextAtPosition((*data.window), (*enemyIt)->GetPosition(), (*data.baseFont), IntStringConcatenate(bullet->GetDamage(), ""), 24);
	//		_uiManager->GetDamageTextList()->push_back(text);
	//	}
	//}
	//enemyIt++;
}

