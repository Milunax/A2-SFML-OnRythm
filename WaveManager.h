#pragma once
#include <SFML/Graphics.hpp>
#include "EnemySpawner.h"
#include <vector>
#include <iostream>
#include "Player.h"

class WaveManager
{
	public:
		WaveManager(sf::RenderWindow& window, Player* player);
		void Update(float deltaTime);
		void SpawnWave();
		void MoveAllEnemies();
		void DrawAllEnemies(sf::RenderWindow& window);

	private:
		std::vector<EnemySpawner*> _spawners;
		std::vector<Enemy*> _enemyList;
		float _timer;
		float _spawnTime;
		int _numberOfEnemiesToSpawn = 3;
		int _maxEnemyCount = 32;

		Player* _player;
};

