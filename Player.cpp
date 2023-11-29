#include "Player.h"

Player::Player(sf::Color color, sf::Vector2f startPos, int radius, float maxHealth, float speed) : Entity(startPos, maxHealth, speed)
{
	_circle.setFillColor(color);
	_circle.setPosition(startPos);
	_circle.setRadius(radius);
}

sf::CircleShape& Player::getPlayerShape() {
	return _circle;
}