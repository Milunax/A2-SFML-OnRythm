#include "EnemySpawner.h"

EnemySpawner::EnemySpawner(sf::Vector2f position) 
{
	_position = position;
}

Enemy* EnemySpawner::InstantiateEnemy(Player* enemyTarget) 
{
	Enemy* enemy = new Enemy(20.0f, sf::Color::Red, _position, 10.0f, 20.0f);
	enemy->SetTarget(enemyTarget);
	return enemy;

}

