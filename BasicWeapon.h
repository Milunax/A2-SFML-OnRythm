#pragma once
#include "Weapon.h"
#include "Bullet.h"

class BasicWeapon : public Weapon 
{
	public :
		BasicWeapon(float damages, float attackRate, WeaponData weaponData);
		void Update(RefsData data);
		Bullet* InstanciateBullet(sf::Vector2f direction);
		void Attack();
		//void CheckCollision(RefsData data);
	private :
		int _level;
		std::vector<Bullet*> _bulletList;
};
