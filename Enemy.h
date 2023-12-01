#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Math.h"
#include <cmath>

struct EnemyData
{
	float Radius;
	sf::Color Color;
	float MaxHealth;
	float Speed;
};

extern EnemyData normalEnemy;
extern EnemyData bossEnemy;

class Enemy : public Entity 
{
	public :
		Enemy(EnemyData data, sf::Vector2f startPos, Player* target);
		~Enemy();
		void SetTarget(Player* target);
		void Move();
		bool CollidingWithPlayer();
		void Draw(sf::RenderWindow& window);
	private :
		float _radius;
		sf::Color _color;
		Player* _player;
};
