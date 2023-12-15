#pragma once
#include "Weapon.h"
#include "Bullet.h"
#include "Enemy.h"

class CircularWeapon : Weapon
{
	public :
		CircularWeapon(float radius, float damages, int baseBulletNumber, float rotationSpeed, WeaponData weaponData, float attackRate = 0);
		void Draw(RefsData data);
		void Update(RefsData data);
		void MoveBullets(RefsData data);
		void CheckCollision(RefsData data, Bullet* bullet);
	private :
		float _radius;
		float _rotationSpeed;
		float _rotationAngle;
		int _baseBulletNumber;
		std::vector<Bullet*> _bulletList;
};
