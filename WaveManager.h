#pragma once
#include <SFML/Graphics.hpp>
#include "EnemySpawner.h"
#include <vector>
#include <iostream>
#include "Player.h"
#include "Data.h"

class WaveManager
{
	public:
		WaveManager(sf::RenderWindow& window, Player* player);
		void Update(Data data);
		void SpawnWave();
		void SpawnBoss();
		void SetEnemiesNextPosition();
		void MoveAllEnemies(float deltaTime);
		void CheckCollisionAllEnemies();
		void EraseDeadEnemies();
		void DrawAllEnemies(sf::RenderWindow& window);
		std::vector<Enemy*>* GetEnemyList();
	private:
		std::vector<EnemySpawner*> _spawners;
		std::vector<Enemy*> _enemyList;
		float _timer;
		float _spawnTime;
		int _numberOfEnemiesToSpawn;
		int _maxEnemyCount;

		Player* _player;
};

