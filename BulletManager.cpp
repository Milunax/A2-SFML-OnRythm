#include "BulletManager.h"

BulletManager::BulletManager(){
	_player = nullptr;
	_enemyList = nullptr;
	_waveManager = nullptr;
	_boss = nullptr;
	_uiManager = nullptr;
}

void BulletManager::Init(Player* player, WaveManager* waveManager, UIManager* uiManager)
{
	_player = player;
	_waveManager = waveManager;
	_enemyList = waveManager->GetEnemyList();
	_uiManager = uiManager;
}

void BulletManager::Update(RefsData data)
{
	UpdateTimer(data);
	if (_fireTimer >= 1 / _player->GetFireRate()) {
		FireWeapon();
		//std::cout << _bulletList.size() << std::endl;
		_fireTimer = 0.0f;
	}
	for (Bullet* bullet : _bulletList) {
		bullet->Move(data.deltaTime);
	}
	CheckCollisionAllBullets(data);
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

Bullet* BulletManager::InstanciateBullet(sf::Vector2f direction)
{
	Bullet* bullet = new Bullet(sf::Color::Yellow, 10, _player->GetPosition(), direction, 1000, _player->GetDamages());
	//std::cout << "a tir�" << std::endl;
	return bullet;
}

void BulletManager::CheckCollisionAllBullets(RefsData data)
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
				sf::Text* text = CreateTextAtPosition((*data.window), (*enemyIt)->GetPosition(), (*data.baseFont), IntStringConcatenate((*bulletIt)->GetDamage(), ""), 24);
				_uiManager->GetDamageTextList()->push_back(text);
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

void BulletManager::FireWeapon()
{
	std::vector<sf::Vector2f> directionList = {
		sf::Vector2f(1,0),
		sf::Vector2f(0,1),
		sf::Vector2f(-1,0),
		sf::Vector2f(0,-1),
		sf::Vector2f(1, 1),
		sf::Vector2f(-1, -1),
		sf::Vector2f(1, -1),
		sf::Vector2f(-1, 1),
	};

	switch (_player->GetTimesWeaponUpgraded())
	{
	case 0 : 
		_bulletList.push_back(InstanciateBullet(_player->GetOrientationDirection()));
		//std::cout << "case 0" << std::endl;
		break;
	case 1 :
		_bulletList.push_back(InstanciateBullet(_player->GetOrientationDirection()));
		_bulletList.push_back(InstanciateBullet(-_player->GetOrientationDirection()));
		//std::cout << "case 1" << std::endl;
		break;
	case 2 :
		_bulletList.push_back(InstanciateBullet(directionList[0]));
		_bulletList.push_back(InstanciateBullet(directionList[1]));
		_bulletList.push_back(InstanciateBullet(directionList[2]));
		_bulletList.push_back(InstanciateBullet(directionList[3]));
		//std::cout << "case 2" << std::endl;
		break;
	case 3 :
		for (sf::Vector2f direction : directionList)
		{
			_bulletList.push_back(InstanciateBullet(direction));
		}
		//std::cout << "case 3" << std::endl;
		break;
	default : 
		for (sf::Vector2f direction : directionList)
		{
			_bulletList.push_back(InstanciateBullet(direction));
		}
		//std::cout << "case default" << std::endl;
		break;
	}
}