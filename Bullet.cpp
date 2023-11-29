#include "Bullet.h"

Bullet::Bullet(sf::Color color, int radius, sf::Vector2f startPos, sf::Vector2f direction, float speed) {
	_color = color;
	_circle.setPosition(startPos);
	_radius = radius;
	_speed = speed;
}

void Bullet::Draw(sf::RenderWindow& window)
{
	sf::CircleShape shape;
	shape.setRadius(_radius);
	shape.setFillColor(_color);
	shape.setPosition(_position);
	window.draw(shape);
}

//void Bullet::Move(float deltaTime){
//	_position.x = _position.x - deltaTime * _speed;
//}