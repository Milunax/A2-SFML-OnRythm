#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Math.h"


class Enemy : public Entity 
{
	public :
		Enemy(float radius, sf::Color color, sf::Vector2f startPos, float maxHealth, float speed);
		void Draw(sf::RenderWindow& window);
		void SetTarget(Entity* target);
		void Move();
	private :
		float _radius;
		sf::Color _color;
		Entity* _target;
};