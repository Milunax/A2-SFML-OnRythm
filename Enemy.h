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
	float ExperienceDropped;
	int ScoreToAdd;
};

extern EnemyData normalEnemy;
extern EnemyData bossEnemy;

class Enemy : public Entity 
{
	public :
		Enemy(EnemyData data, sf::Vector2f startPos, Player* target);
		void SetTarget(Player* target);
		void SetNextPosition(float moveMultiplier);
		void Update(float deltaTime, float moveMultiplier);
		void Move(float deltaTime, float moveMultiplier);
		void Attack();
		void ScaleStats(float scaleFactor);
		CircleCollider GetCollider();
		float GetDamage();
		float GetExperienceDropped();
		int GetScore();
		void Draw(sf::RenderWindow& window);
	private :
		float _radius;
		sf::Color _color;
		sf::Vector2f _nextPosition;
		float _moveDistance;

		float _damage;
		float _attackTimer;
		float _attackSpeed;

		float _experienceDropped;

		int _scoreToAdd;

		Player* _player;
};
