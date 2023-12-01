#pragma once
#include "Entity.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <vector>

class Bullet;

class Player : public Entity {
	public :
		Player(sf::Color color, sf::Vector2f startPos, int radius, float maxHealth, float speed);
		void Draw(sf::RenderWindow& window);
		sf::CircleShape& GetPlayerShape();
		void SetColor(sf::Color color);
		void Update(float deltaTime);
		void UpdateTimer(float deltaTime);
		void Move(float deltaTime);
		Bullet* Shoot();
		void DrawBullets(sf::RenderWindow& window);
		void UpdateBullets(float deltaTime);
		float GetRadius();
	private :
		sf::CircleShape _circle;
		sf::Color _color;
		float _radius;
		sf::Vector2f _moveDirection = { 0, 0 };
		sf::Vector2f _orientationDirection = { 1, 0 };
		float _fireTimer = 0.0f;
		float _bulletFireRate = 1.0f;
		std::vector<Bullet*> _bulletList;
};
