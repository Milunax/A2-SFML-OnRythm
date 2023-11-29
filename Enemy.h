#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Math.h"


class Enemy : public Entity 
{
	public :
		Enemy(sf::Vector2f size, sf::Color color, sf::Vector2f startPos, float maxHealth, float speed);
		void Draw(sf::RenderWindow& window);
		void SetTarget(Entity* target);
		void Move(float deltaTime);
	private :
		sf::Vector2f _size;
		sf::Color _color;
		Entity* _target;
};