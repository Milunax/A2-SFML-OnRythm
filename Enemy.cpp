#include "Enemy.h"

Enemy::Enemy(sf::Vector2f startPos,float maxHealth, float speed, sf::Vector2f size, sf::Color color) : Entity(startPos, maxHealth, speed)
{
	_enemyShape.setPosition(startPos);
	_enemyShape.setSize(size);
	_enemyShape.setFillColor(color);
}

sf::RectangleShape& Enemy::GetEnemyShape() 
{
	return _enemyShape;
}

void Enemy::SetTarget(Entity* target) 
{
	_target = target;
}

void Enemy::Move() 
{

}