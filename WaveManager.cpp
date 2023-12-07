#include "WaveManager.h"

WaveManager::WaveManager(float timer, float spawnTime, int numberOfEnemiesToSpawn, int maxEnemyCount)
{
	_timer = timer;
	_spawnTime = spawnTime;
	_numberOfEnemiesToSpawn = numberOfEnemiesToSpawn;
	_maxEnemyCount = maxEnemyCount;

	_player = nullptr;
}

void WaveManager::Init(sf::RenderWindow& window, Player* player)
{
	std::vector<sf::Vector2f> positions{
		sf::Vector2f(-50, -50),
		sf::Vector2f(window.getSize().x / 2, -50),
		sf::Vector2f(window.getSize().x + 50, -50),
		sf::Vector2f(window.getSize().x + 50, window.getSize().y / 2),
		sf::Vector2f(window.getSize().x + 50, window.getSize().y + 50),
		sf::Vector2f(window.getSize().x / 2, window.getSize().y + 50),
		sf::Vector2f(-50, window.getSize().y + 50),
		sf::Vector2f(-50, window.getSize().y / 2)
	};

	for (sf::Vector2f position : positions) {
		_spawners.push_back(new EnemySpawner(position));
	}

	_player = player;
}

void WaveManager::Update(RefsData data) 
{
	UpdateAllEnemies(data.deltaTime);
	CheckCollisionAllEnemies();
	_timer += data.deltaTime;
	if (_timer > _spawnTime) 
	{
		SpawnWave();
		_timer = 0;
	}
	EraseDeadEnemies();
}

void WaveManager::SpawnWave()
{
	int numberToSpawn = _numberOfEnemiesToSpawn;
	for (int i = 0; i < _spawners.size(); i++)
	{
		if (_enemyList.size() < _maxEnemyCount) 
		{
			if (numberToSpawn < _spawners.size() - (i + 1))
			{
				int random = rand() % 2;
				if (numberToSpawn > 0 && random == 1) {
					_enemyList.push_back(_spawners[i]->InstantiateEnemy(normalEnemy, _spawners[i]->GetPosition(), _player));
					numberToSpawn--;
				}
			}
			else
			{
				_enemyList.push_back(_spawners[i]->InstantiateEnemy(normalEnemy, _spawners[i]->GetPosition(), _player));
				numberToSpawn--;
			}
		}
		
		if (_enemyList.size() >= _maxEnemyCount) return;
		if (numberToSpawn <= 0) return;
	}
}

void WaveManager::SpawnBoss() 
{
	int random = rand() % _spawners.size();
	_enemyList.push_back(_spawners[random]->InstantiateEnemy(bossEnemy, _spawners[random]->GetPosition(), _player));
}

void WaveManager::SetEnemiesNextPosition() 
{
	for (Enemy* enemy : _enemyList)
	{
		enemy->SetNextPosition();
	}
}

void WaveManager::UpdateAllEnemies(float deltaTime)
{
	for (Enemy* enemy : _enemyList)
	{
		enemy->Update(deltaTime);
	}
}


void WaveManager::MoveAllEnemies(float deltaTime)
{
	for (Enemy* enemy : _enemyList)
	{
		enemy->Move(deltaTime);
	}
}

void WaveManager::CheckCollisionAllEnemies() 
{
	CircleCollider playerCol = _player->GetCollider();

	for (Enemy* enemy : _enemyList) 
	{
		CircleCollider enemyCol = enemy->GetCollider();
		if (AreCircleCollidersOverlapping(enemyCol, playerCol))
		{
			enemy->Attack();
			ClampCircleOutsideCircle(enemyCol, playerCol);
			enemy->SetPosition(enemyCol.Origin);
		}
	}
}

void WaveManager::EraseDeadEnemies() 
{
	std::vector<Enemy*>::iterator it = _enemyList.begin();
	while (it != _enemyList.end()) 
	{
		if (!(*it)->IsAlive) 
		{
			_player->AddExperience((*it)->GetExperienceDropped());
			delete (*it);
			it = _enemyList.erase(it);
		}
		else 
		{
			it++;
		}
	}
}

void WaveManager::DrawAllEnemies(sf::RenderWindow& window)
{
	for (Enemy* enemy : _enemyList) 
	{
		enemy->Draw(window);
	}

}

std::vector<Enemy*>* WaveManager::GetEnemyList()
{
	return &_enemyList;
}
