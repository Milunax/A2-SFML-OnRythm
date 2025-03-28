#include "Enemy.h"

EnemyData normalEnemy = { 20.0f, sf::Color::Red, 2.0f , 50.0f, 10.0f, 2.0f, 1.0f, 5.0f, 10};
EnemyData bossEnemy = { 40.0f, sf::Color::Magenta, 100.0f , 20.0f, 10.0f, 20.0f, 1.0f, 20.0f, 100};

Enemy::Enemy(EnemyData data, sf::Vector2f startPos, Player* target) : Entity(startPos, data.MaxHealth, data.Speed)
{
	_radius = data.Radius;
	_color = data.Color;
	_moveDistance = data.MoveDistance;

	_damage = data.Damage;
	_attackTimer = 0;
	_attackSpeed = data.AttackSpeed;

	_experienceDropped = data.ExperienceDropped;

	_player = target;

	_scoreToAdd = data.ScoreToAdd;
}

void Enemy::SetTarget(Player* player) 
{
	_player = player;
}

void Enemy::SetNextPosition(float moveMultiplier)
{
	if (_player != nullptr)
	{
		sf::Vector2f direction = _player->GetPosition() - _position;
		Normalize(direction);
		_nextPosition = _position + direction * _moveDistance * moveMultiplier;
		//_nextPosition = _position + sf::Vector2f(3, 1) * _moveDistance;
	}
}

void Enemy::Update(float deltaTime, float moveMultiplier) 
{
	Move(deltaTime, moveMultiplier);
	if(_attackTimer < _attackSpeed) _attackTimer += deltaTime;
}


void Enemy::Move(float deltaTime, float moveMutiplier) 
{
	if (_speed * deltaTime > Distance(_position, _nextPosition)) 
	{
		_position = _nextPosition;
	}
	else 
	{
		sf::Vector2f direction = _nextPosition - _position;
		//sf::Vector2f direction = sf::Vector2f(3, 1);
		Normalize(direction);
		_position = _position + direction * _speed * moveMutiplier * deltaTime;
	}
}

void Enemy::Attack() 
{
	if (_attackTimer >= _attackSpeed) 
	{
		_player->TakeDamage(_damage);
		_attackTimer = 0.0f;
	}
}

void Enemy::ScaleStats(float scaleFactor)
{
	_health *= scaleFactor;
	_damage *= scaleFactor;
}

CircleCollider Enemy::GetCollider() 
{
	CircleCollider collider = { _position, _radius };
	return collider;
}

float Enemy::GetDamage() 
{
	return _damage;
}

float Enemy::GetExperienceDropped() 
{
	return _experienceDropped;
}

int Enemy::GetScore()
{
	return _scoreToAdd;
}


void Enemy::Draw(sf::RenderWindow& window)
{
	sf::CircleShape shape;
	shape.setRadius(_radius);
	shape.setOrigin(sf::Vector2f( (_radius), (_radius) ));
	shape.setFillColor(_color);
	shape.setPosition(_position);
	shape.setOutlineThickness(3.0f);
	window.draw(shape);
}