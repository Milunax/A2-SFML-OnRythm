#include "EnemySpawner.h"

EnemySpawner::EnemySpawner(sf::Vector2f position) 
{
	_position = position;
}

Enemy* EnemySpawner::InstantiateEnemy(EnemyData data, sf::Vector2f position, Player* enemyTarget)
{
	Enemy* enemy = new Enemy(data, position, enemyTarget);
	return enemy;

}

sf::Vector2f EnemySpawner::GetPosition()
{
	return _position;
}