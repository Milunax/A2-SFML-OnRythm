#pragma once
#include "Entity.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <vector>

class Player : public Entity {
	public :
		Player(sf::Color color, sf::Vector2f startPos, int radius, float maxHealth, float speed);
		void Draw(sf::RenderWindow& window);
		sf::CircleShape& GetPlayerShape();
		void Update(float deltaTime, std::vector<Bullet*>& bulletList);
		void UpdateTimer(float deltaTime);
		void Move(float deltaTime);
		Bullet* Shoot();
	private :
		sf::CircleShape _circle;
		sf::Color _color;
		float _radius;
		sf::Vector2f _directon;
		float _fireTimer = 0.0f;
		float _bulletFireRate = 1.0f;
};
