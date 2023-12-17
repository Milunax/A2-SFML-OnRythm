#pragma once
#include "Weapon.h"
#include "Enemy.h"

class CloseWeapon : public Weapon 
{
	public : 
		CloseWeapon(sf::Color color, float radius, float damages, float attackRate, WeaponData weaponData);
		void Update(RefsData data, Player* player);
		void Draw(RefsData data);
		void CheckCollision(std::vector<Enemy*>* enemyList);
		void ScaleStats();
	private :
		sf::Color _color;
		float _radius;
};
