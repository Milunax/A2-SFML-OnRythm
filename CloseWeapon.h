#pragma once
#include "Weapon.h"
#include "Enemy.h"

class CloseWeapon : public Weapon 
{
	public : 
		CloseWeapon(sf::Color color, float radius, float damages, float attackRate, WeaponData weaponData);
		void Update(RefsData data);
		void Draw(RefsData data);
		void CheckCollision(RefsData data);
	private :
		sf::Color _color;
		float _radius;
};
