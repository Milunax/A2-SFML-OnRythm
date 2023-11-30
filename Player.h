#pragma once
#include "Entity.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System/Vector2.hpp>

class Player : public Entity {
	public :
		Player(sf::Color color, sf::Vector2f startPos, int radius, float maxHealth, float speed);
		void Draw(sf::RenderWindow& window);
		sf::CircleShape& GetPlayerShape();
		void Move(float deltaTime);
		void Shoot(float deltaTime);
	private :
		sf::CircleShape _circle;
		sf::Color _color;
		float _radius;
		sf::Vector2f _directon;
		float _fireTimer = 0.0f;
		float _bulletFireRate = 1.0f;
};
