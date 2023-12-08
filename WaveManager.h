#pragma once
#include <SFML/Graphics.hpp>
#include "EnemySpawner.h"
#include <vector>
#include <iostream>
#include "Player.h"
#include "RefsData.h"

class WaveManager
{
	public:
		WaveManager(float timer, float spawnTime, int numberOfEnemiesToSpawn, int maxEnemyCount);
		void Init(sf::RenderWindow& window, Player* player);
		void Update(RefsData data);
		void SpawnWave();
		void SpawnBoss();
		void AugmentScaleFactor();
		void SetEnemiesNextPosition();
		void UpdateAllEnemies(float deltaTime);
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

		float _enemyScaleFactor;
		float _factorAugment;

		Player* _player;
};

