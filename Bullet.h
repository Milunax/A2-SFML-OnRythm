#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>

class Bullet {
	public :
		Bullet(sf::Color color, int radius, sf::Vector2f startPos, sf::Vector2f direction, float speed);
		//void Move(float deltaTime);
	private :
		float _speed;
		sf::Vector2f _position;
		sf::Vector2f _direction;
		sf::CircleShape _circle;
		sf::Vector2f _direection;
};
