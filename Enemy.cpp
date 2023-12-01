#include "Enemy.h"

EnemyData normalEnemy = { 20.0f, sf::Color::Red, 10.0f , 20.0f };
EnemyData bossEnemy = { 40.0f, sf::Color::Magenta, 100.0f , 20.0f };

Enemy::Enemy(EnemyData data, sf::Vector2f startPos, Player* target) : Entity(startPos, data.MaxHealth, data.Speed)
{
	_radius = data.Radius;
	_color = data.Color;
	_player = target;
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