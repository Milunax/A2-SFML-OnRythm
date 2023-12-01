#include "Enemy.h"

Enemy::Enemy(float radius, sf::Color color, sf::Vector2f startPos,float maxHealth, float speed) : Entity(startPos, maxHealth, speed)
{
	_radius = radius;
	_color = color;
	_player = nullptr;
}

Enemy::~Enemy() 
{
	
}

void Enemy::SetTarget(Player* player) 
{
	_player = player;
}

void Enemy::Move() 
{
	if (_player != nullptr) 
	{
		sf::Vector2f direction = _player->GetPosition() - _position;
		Normalize(direction);
		_position = _position + direction * _speed;
	}
	
}

bool Enemy::CollidingWithPlayer()
{
	sf::Vector2f distanceVector = _player->GetPosition() - _position;
	float distance = Magnitude(distanceVector);
	if (distance <= (_radius + _player->GetRadius())) 
	{
		return true;
	}
	return false;
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