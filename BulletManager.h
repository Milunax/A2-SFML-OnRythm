#pragma once
#include <vector>
#include <iostream>
#include "Bullet.h"
#include "Player.h"
#include "Enemy.h"
#include "WaveManager.h"
#include "UIManager.h"

class BulletManager 
{
	public:
		BulletManager();
		void Init(Player* player, WaveManager* waveManager, UIManager* uiManager);
		void Update(RefsData data);
		void UpdateTimer(RefsData data);
		void DrawBullets(RefsData data);
		Bullet* InstanciateBullet(sf::Vector2f direction);
		void CheckCollisionAllBullets(RefsData data);
		void FireWeapon();
	private:
		Player* _player;
		WaveManager* _waveManager;
		UIManager* _uiManager;
		std::vector<Bullet*> _bulletList;
		std::vector<Enemy*>* _enemyList;
		Enemy* _boss;
		float _fireTimer = 0.0f;
		int _score;
};
