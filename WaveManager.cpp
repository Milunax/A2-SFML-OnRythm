#include "WaveManager.h"

WaveManager::WaveManager(sf::RenderWindow& window, Player* player) 
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

	_timer = 0;
	_spawnTime = 5;
	_numberOfEnemiesToSpawn = 3;
	_maxEnemyCount = 32;

	_player = player;
}

void WaveManager::Update(float deltaTime) 
{
	_timer += deltaTime;
	if (_timer > _spawnTime) 
	{
		SpawnWave();
		_timer = 0;
	}
	CheckCollisionAllEnemies();
}

void WaveManager::SpawnWave()
{
	int numberToSpawn = _numberOfEnemiesToSpawn;
	for (int i = 0; i < _spawners.size(); i++)
	{
		if (numberToSpawn < _spawners.size() - (i + 1)) 
		{
			int random = rand() % 2;
			if (numberToSpawn > 0 && random == 1) {
				_enemyList.push_back(_spawners[i]->InstantiateEnemy(_player));
				numberToSpawn--;
			}
		}
		else 
		{
			_enemyList.push_back(_spawners[i]->InstantiateEnemy(_player));
			numberToSpawn--;
		}
		if (numberToSpawn <= 0) return;
	}
}

void WaveManager::MoveAllEnemies() 
{
	for (Enemy* enemy : _enemyList)
	{
		enemy->Move();
	}
}

void WaveManager::CheckCollisionAllEnemies() 
{
	std::vector<Enemy*>::iterator it = _enemyList.begin();
	while (it != _enemyList.end()) {
		if ((*it)->CollidingWithPlayer())
		{
			Enemy* enemy = (*it);
			it = _enemyList.erase(it);
			delete enemy;
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