#include "BasicWeapon.h"

BasicWeapon::BasicWeapon(float damages, float attackRate, WeaponData weaponData) : Weapon(damages, attackRate, weaponData)
{
}

void BasicWeapon::Update(RefsData data, Player* player)
{
	Weapon::Update(data, player);

	for (Bullet* bullet : _bulletList) 
	{
		bullet->Move(data.deltaTime);
	}


	UpdateTimer(data);
	if (_fireTimer > 1 / _attackRate) {
		Attack();
		_fireTimer = 0.0f;
	}

	CheckAllPosition(data);

	//std::cout << _level << std::endl;
}

void BasicWeapon::CheckAllPosition(RefsData data)
{
	std::vector<Bullet*>::iterator it = _bulletList.begin();
	while (it != _bulletList.end()) {
		if ((*it)->IsBulletOutOfWindow(data))
		{
			delete *it;
			it = _bulletList.erase(it);
		}
		else
		{
			it++;
		}
	}
}

void BasicWeapon::CheckCollision(std::vector<Enemy*>* enemyList)
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
				delete (*bulletIt);

				bulletIt = _bulletList.erase(bulletIt);
			}
			else
			{
				bulletIt++;
			}
		}
		enemyIt++;
	}
}

Bullet* BasicWeapon::InstanciateBullet(sf::Vector2f direction)
{
	Bullet* bullet = new Bullet(sf::Color::Yellow, 10, _position, direction, 1000, _damages);
	//std::cout << "a tiré" << std::endl;
	return bullet;
}

void BasicWeapon::Attack()
{
	std::vector<sf::Vector2f> directionList = {
	sf::Vector2f(1,0),
	sf::Vector2f(0,1),
	sf::Vector2f(-1,0),
	sf::Vector2f(0,-1),
	sf::Vector2f(1, 1),
	sf::Vector2f(-1, -1),
	sf::Vector2f(1, -1),
	sf::Vector2f(-1, 1),
	};

	switch (_level)
	{
		case 1:
			_bulletList.push_back(InstanciateBullet(_orientationDirection));
			break;
		case 2:
			_bulletList.push_back(InstanciateBullet(_orientationDirection));
			_bulletList.push_back(InstanciateBullet(-_orientationDirection));
			break;
		case 3:
			_bulletList.push_back(InstanciateBullet(directionList[0]));
			_bulletList.push_back(InstanciateBullet(directionList[1]));
			_bulletList.push_back(InstanciateBullet(directionList[2]));
			_bulletList.push_back(InstanciateBullet(directionList[3]));
			break;
		case 4:
			for (sf::Vector2f direction : directionList)
			{
				_bulletList.push_back(InstanciateBullet(direction));
			}
			break;
		default:
			for (sf::Vector2f direction : directionList)
			{
				_bulletList.push_back(InstanciateBullet(direction));
			}
			std::cout << "case default" << std::endl;
			break;
	}
}

void BasicWeapon::Draw(RefsData data)
{
	for (Bullet* bullet : _bulletList) 
	{
		bullet->Draw(*data.window);
	}
}

void BasicWeapon::ScaleStats()
{
	if (_level % 2 == 0) _damages += 1.0f;
	if (_level % 3 == 0) _attackRate *= 2.0f;
}


