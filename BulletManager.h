#pragma once
#include <vector>
#include <iostream>
#include "Bullet.h"
#include "Player.h"
#include "Enemy.h"
#include "WaveManager.h"

class BulletManager 
{
	public:
		BulletManager(Player* player, std::vector<Enemy*>* enemyList, WaveManager* waveManager);
		void Update(Data data);
		void UpdateTimer(Data data);
		void DrawBullets(Data data);
		Bullet* InstanciateBullet();
		void CheckCollisionAllBullets();
		void CheckIfBossExist();
	private:
		Player* _player;
		WaveManager* _waveManager;
		std::vector<Bullet*> _bulletList;
		std::vector<Enemy*>* _enemyList;
		Enemy* _boss;
		float _fireTimer = 0.0f;
		float _bulletFireRate = 1.0f;
};
