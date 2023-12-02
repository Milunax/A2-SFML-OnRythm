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
		void SpawnBoss();
		void SetEnemiesNextPosition();
		void MoveAllEnemies(float deltaTime);
		void CheckCollisionAllEnemies();
		void DrawAllEnemies(sf::RenderWindow& window);

	private:
		std::vector<EnemySpawner*> _spawners;
		std::vector<Enemy*> _enemyList;
		float _timer;
		float _spawnTime;
		int _numberOfEnemiesToSpawn;
		int _maxEnemyCount;

		Enemy* _boss;

		Player* _player;
};

