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
	_spawnTime = 2;

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

	for (Enemy* enemy : _enemyList) 
	{
		enemy->Move(deltaTime);
	}
}

void WaveManager::SpawnWave()
{
	for (EnemySpawner* spawner : _spawners)
	{
		_enemyList.push_back(spawner->InstantiateEnemy(_player));
	}
}

void WaveManager::DrawAllEnemies(sf::RenderWindow& window)
{
	for (Enemy* enemy : _enemyList) 
	{
		enemy->Draw(window);
	}
}