#include "EnemySpawner.h"

EnemySpawner::EnemySpawner(sf::Vector2f position) 
{
	_position = position;
}

Enemy* EnemySpawner::InstantiateEnemy(Entity* enemyTarget) 
{
	Enemy* enemy = new Enemy(sf::Vector2f(50, 50), sf::Color::Red, _position, 10, 20);
	enemy->SetTarget(enemyTarget);
	return enemy;

}

