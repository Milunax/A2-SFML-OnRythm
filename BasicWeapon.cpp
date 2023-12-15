#include "BasicWeapon.h"

BasicWeapon::BasicWeapon(float damages, float attackRate, WeaponData weaponData) : Weapon(damages, attackRate, weaponData)
{
	_level = 0;
}

void BasicWeapon::Update(RefsData data)
{
	UpdateTimer(data);
	if (_fireTimer > 1 / _attackRate) {
		Attack();
		_fireTimer = 0.0f;
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
	case 0:
		_bulletList.push_back(InstanciateBullet(_orientationDirection));
		std::cout << "case 0" << std::endl;
		break;
	case 1:
		_bulletList.push_back(InstanciateBullet(_orientationDirection));
		_bulletList.push_back(InstanciateBullet(-_orientationDirection));
		std::cout << "case 1" << std::endl;
		break;
	case 2:
		_bulletList.push_back(InstanciateBullet(directionList[0]));
		_bulletList.push_back(InstanciateBullet(directionList[1]));
		_bulletList.push_back(InstanciateBullet(directionList[2]));
		_bulletList.push_back(InstanciateBullet(directionList[3]));
		std::cout << "case 2" << std::endl;
		break;
	case 3:
		for (sf::Vector2f direction : directionList)
		{
			_bulletList.push_back(InstanciateBullet(direction));
		}
		std::cout << "case 3" << std::endl;
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
