#include "BulletManager.h"

BulletManager::BulletManager(Player* player, std::vector<Enemy*>* enemyList, WaveManager* waveManager){
	_player = player;
	_enemyList = enemyList;
	_waveManager = waveManager;
}

void BulletManager::Update(Data data)
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
	CheckIfBossExist();
	CheckCollisionAllBullets();
}

void BulletManager::UpdateTimer(Data data)
{
	_fireTimer += data.deltaTime;
	//std::cout << _fireTimer << std::endl;
}

void BulletManager::DrawBullets(Data data) {
	for (Bullet* bullet : _bulletList) {
		bullet->Draw(*data.window);
	}
}

Bullet* BulletManager::InstanciateBullet()
{
	Bullet* bullet = new Bullet(sf::Color::Yellow, 10, _player->GetPosition(), _player->GetOrientationDirection(), 1000);
	//std::cout << "a tiré" << std::endl;
	return bullet;
}

void BulletManager::CheckCollisionAllBullets() 
{
	std::vector<Bullet*>::iterator bulletIt = _bulletList.begin();

	while (bulletIt != _bulletList.end()) 
	{
		CircleCollider bulletCol = (*bulletIt)->GetCollider();
		std::vector<Enemy*>::iterator enemyIt = _enemyList->begin();

		while (enemyIt != _enemyList->end())
		{
			CircleCollider enemyCol = (*enemyIt)->GetCollider();
			if (AreCircleCollidersOverlapping(bulletCol, enemyCol))
			{
				delete (*bulletIt);
				delete (*enemyIt);
				
				bulletIt = _bulletList.erase(bulletIt);
				enemyIt = _enemyList->erase(enemyIt);
			}
			else 
			{
				enemyIt++;
			}
		}

		if (_boss != nullptr) {
			CircleCollider bossCol = _boss->GetCollider();
			if (AreCircleCollidersOverlapping(bulletCol, bossCol)) 
			{
				delete _boss;
				_boss = nullptr;
				_waveManager->SetBoss(nullptr);

				delete (*bulletIt);
				bulletIt = _bulletList.erase(bulletIt);
			}
		}

		if (_bulletList.size() != 0) {
			bulletIt++;
		}
	
	}
}

void BulletManager::CheckIfBossExist()
{
	if (_boss == nullptr) {
		_boss = _waveManager->GetBoss();
	}
}

