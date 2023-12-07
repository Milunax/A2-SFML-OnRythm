#include "BulletManager.h"

BulletManager::BulletManager(){
	_player = nullptr;
	_enemyList = nullptr;
	_waveManager = nullptr;
}

void BulletManager::Init(Player* player, WaveManager* waveManager)
{
	_player = player;
	_waveManager = waveManager;
	_enemyList = waveManager->GetEnemyList();
}

void BulletManager::Update(RefsData data)
{
	UpdateTimer(data);
	if (_fireTimer >= 1 / _bulletFireRate) {
		_bulletList.push_back(InstanciateBullet());
		//std::cout << _bulletList.size() << std::endl;
		_fireTimer = 0.0f;
	}
	for (Bullet* bullet : _bulletList) {
		bullet->CheckPosition(data, _bulletList);
		bullet->Move(data.deltaTime);
	}
	CheckCollisionAllBullets();
}

void BulletManager::UpdateTimer(RefsData data)
{
	_fireTimer += data.deltaTime;
	//std::cout << _fireTimer << std::endl;
}

void BulletManager::DrawBullets(RefsData data) {
	for (Bullet* bullet : _bulletList) {
		bullet->Draw(*data.window);
	}
}

Bullet* BulletManager::InstanciateBullet()
{
	Bullet* bullet = new Bullet(sf::Color::Yellow, 10, _player->GetPosition(), _player->GetOrientationDirection(), 1000, 1);
	//std::cout << "a tir�" << std::endl;
	return bullet;
}

void BulletManager::CheckCollisionAllBullets() 
{
	std::vector<Enemy*>::iterator enemyIt = _enemyList->begin();


	while (enemyIt != _enemyList->end())
	{
		CircleCollider enemyCol = (*enemyIt)->GetCollider();
		std::vector<Bullet*>::iterator bulletIt = _bulletList.begin();

		while (bulletIt != _bulletList.end())
		{
			CircleCollider bulletCol = (*bulletIt)->GetCollider();
			if (AreCircleCollidersOverlapping(bulletCol, enemyCol))
			{
				(*enemyIt)->TakeDamage((*bulletIt)->GetDamage());

				delete (*bulletIt);
				
				bulletIt = _bulletList.erase(bulletIt);
			}
			else 
			{
				bulletIt++;
			}
		}
		enemyIt++;
	}
}