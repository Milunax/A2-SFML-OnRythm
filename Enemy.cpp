#include "Enemy.h"

Enemy::Enemy(sf::Vector2f size, sf::Color color, sf::Vector2f startPos,float maxHealth, float speed) : Entity(startPos, maxHealth, speed)
{
	_size = size;
	_color = color;
	_target = nullptr;
}

void Enemy::SetTarget(Entity* target) 
{
	_target = target;
}

void Enemy::Move(float deltaTime) 
{
	if (_target != nullptr) 
	{
		sf::Vector2f direction = _target->GetPosition() - _position;
		Normalize(direction);
		_position = _position + direction * _speed * deltaTime;
	}
	
}

void Enemy::Draw(sf::RenderWindow& window)
{
	sf::RectangleShape shape;
	shape.setSize(_size);
	shape.setOrigin(sf::Vector2f( (_size.x / 2), (_size.y / 2) ));
	shape.setFillColor(_color);
	shape.setPosition(_position);
	window.draw(shape);
}