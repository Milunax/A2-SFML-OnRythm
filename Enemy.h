#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Math.h"
#include <cmath>


class Enemy : public Entity 
{
	public :
		Enemy(float radius, sf::Color color, sf::Vector2f startPos, float maxHealth, float speed);
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