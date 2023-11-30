#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>

class Bullet {
	public :
		Bullet(sf::Color color, int radius, sf::Vector2f startPos, sf::Vector2f direction, float speed);
		~Bullet();
		void Draw(sf::RenderWindow& window);
		void Move(float deltaTime);
	private :
		sf::CircleShape _circle;
		float _radius;
		sf::Color _color;
		float _speed;
		sf::Vector2f _position;
		sf::Vector2f _direction;
};
