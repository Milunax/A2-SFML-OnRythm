#include "EnemySpawner.h"

EnemySpawner::EnemySpawner(sf::Vector2f position, float spawnRate) 
{
	_position = position;
	_timer = 0;
	_spawnRate = spawnRate;
}

void EnemySpawner::Update(float deltaTime, std::vector<Enemy*>& enemyList, Entity* enemyTarget)
{
	UpdateTimer(deltaTime);
	if (_timer > 3) 
	{
		enemyList.push_back(InstantiateEnemy(enemyTarget));
		_timer = 0;
	}
}

Enemy* EnemySpawner::InstantiateEnemy(Entity* enemyTarget) 
{
	Enemy* enemy = new Enemy(sf::Vector2f(50, 50), sf::Color::Red, _position, 10, 100);
	enemy->SetTarget(enemyTarget);
	return enemy;

}

void EnemySpawner::UpdateTimer(float deltaTime) 
{
	_timer += deltaTime;
}
