#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Math.h"
#include <cmath>
#include "Collider.h"

struct EnemyData
{
	float Radius;
	sf::Color Color;
	float MaxHealth;
	float Speed;
	float MoveDistance;
	float Damage;
	float AttackSpeed;
};

extern EnemyData normalEnemy;
extern EnemyData bossEnemy;

class Enemy : public Entity 
{
	public :
		Enemy(EnemyData data, sf::Vector2f startPos, Player* target);
		~Enemy();
		void SetTarget(Player* target);
		void SetNextPosition();
		void Update(float deltaTime);
		void Move(float deltaTime);
		void Attack();
		CircleCollider GetCollider();
		float GetDamage();
		void Draw(sf::RenderWindow& window);
	private :
		float _radius;
		sf::Color _color;
		sf::Vector2f _nextPosition;
		float _moveDistance;

		float _damage;
		float _attackTimer;
		float _attackSpeed;

		Player* _player;
};
