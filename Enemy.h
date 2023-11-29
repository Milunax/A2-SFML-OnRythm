#pragma once
#include "Entity.h"
#include <SFML/Graphics.hpp>


class Enemy : public Entity {
	public :
		Enemy(sf::Vector2f startPos, float maxHealth, float speed, sf::Vector2f size, sf::Color color);
		sf::RectangleShape& GetEnemyShape();
		void SetTarget(Entity* target);
		void Move();
	private :
		sf::RectangleShape _enemyShape;
		Entity* _target;
};