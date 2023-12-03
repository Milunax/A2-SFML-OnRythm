#pragma once
#include <vector>
#include <iostream>
#include "Bullet.h"
#include "Player.h"
#include "Enemy.h"

class BulletManager 
{
	public:
		BulletManager(Player* player, std::vector<Enemy*>* enemyList);
		void Update(Data data);
		void UpdateTimer(Data data);
		void DrawBullets(Data data);
		Bullet* InstanciateBullet();
		void CheckCollisionAllBullets();
	private:
		Player* _player;
		std::vector<Bullet*> _bulletList;
		std::vector<Enemy*>* _enemyList;
		float _fireTimer = 0.0f;
		float _bulletFireRate = 1.0f;
};
