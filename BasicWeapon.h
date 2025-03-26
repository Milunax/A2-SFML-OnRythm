#pragma once
#include "Weapon.h"
#include "Bullet.h"

class BasicWeapon : public Weapon 
{
	public :
		BasicWeapon(float damages, float attackRate, WeaponData weaponData);
		void Update(RefsData data, Player* player);
		void CheckAllPosition(RefsData data);
		void CheckCollision(std::vector<Enemy*>* enemyList);
		Bullet* InstanciateBullet(sf::Vector2f direction);
		void Attack();
		void Draw(RefsData data);
		void ScaleStats();
	private :
		std::vector<Bullet*> _bulletList;
};
