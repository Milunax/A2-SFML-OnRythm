#pragma once
#include <SFML/System/Vector2.hpp>
#include "Enemy.h"
#include <vector>

class EnemySpawner 
{
	public :
		EnemySpawner(sf::Vector2f position, float spawnRate);
		void Update(float deltaTime, std::vector<Enemy*>& enemyList, Entity* enemyTarget);
		Enemy* InstantiateEnemy(Entity* enemyTarget);
		void UpdateTimer(float deltaTime);
	private :
		sf::Vector2f _position;
		float _timer;
		float _spawnRate;
};
