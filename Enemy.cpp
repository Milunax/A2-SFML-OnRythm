#include "Enemy.h"

Enemy::Enemy(float radius, sf::Color color, sf::Vector2f startPos,float maxHealth, float speed) : Entity(startPos, maxHealth, speed)
{
	_radius = radius;
	_color = color;
	_target = nullptr;
}

void Enemy::SetTarget(Entity* target) 
{
	_target = target;
}

void Enemy::Move() 
{
	if (_target != nullptr) 
	{
		sf::Vector2f direction = _target->GetPosition() - _position;
		Normalize(direction);
		_position = _position + direction * _speed;
	}
	
}

void Enemy::Draw(sf::RenderWindow& window)
{
	sf::CircleShape shape;
	shape.setRadius(_radius);
	shape.setOrigin(sf::Vector2f( (_radius), (_radius) ));
	shape.setFillColor(_color);
	shape.setPosition(_position);
	window.draw(shape);
}