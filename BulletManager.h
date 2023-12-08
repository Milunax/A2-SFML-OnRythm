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
		BulletManager();
		void Init(Player* player, WaveManager* waveManager);
		void Update(RefsData data);
		void UpdateTimer(RefsData data);
		void DrawBullets(RefsData data);
		Bullet* InstanciateBullet(sf::Vector2f direction);
		void CheckCollisionAllBullets();
		void FireWeapon();
	private:
		Player* _player;
		WaveManager* _waveManager;
		std::vector<Bullet*> _bulletList;
		std::vector<Enemy*>* _enemyList;
		Enemy* _boss;
		float _fireTimer = 0.0f;
};
