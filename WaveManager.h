#pragma once
#include <SFML/Graphics.hpp>
#include "EnemySpawner.h"
#include <vector>
#include <iostream>
#include "Player.h"
#include "RefsData.h"
#include "ParticleSystem.h"
#include "UIManager.h"

class WaveManager
{
	public:
		WaveManager(float timer, float spawnTime, int numberOfEnemiesToSpawn, int maxEnemyCount, float factorAugment);
		void Init(sf::RenderWindow& window, GameManager* gameManager, Player* player, ParticleSystem* particleSystem, UIManager* uiManager);
		void Update(RefsData data);
		void SpawnWave();
		void SpawnBoss();
		void ScaleWave();
		void SetMoveMultiplier(float value);
		void AugmentScaleFactor();
		void SetEnemiesNextPosition();
		void UpdateAllEnemies(float deltaTime);
		void CheckCollisionAllEnemies();
		void ShowEnemiesDamageTaken(RefsData data);
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

		float _enemyMoveMultiplier;

		float _enemyScaleFactor;
		float _factorAugment;


		GameManager* _gameManager;
		Player* _player;
		ParticleSystem* _particleSystem;
		UIManager* _uiManager;
};

