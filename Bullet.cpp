#include "Bullet.h"
#include "Math.h"

Bullet::Bullet(sf::Color color, int radius, sf::Vector2f startPos, sf::Vector2f direction, float speed) {
	_color = color;
	_position = startPos;
	_radius = radius;
	_speed = speed;
	_direction = direction;
	Normalize(_direction);
}

Bullet::~Bullet() {
	 
}

void Bullet::Draw(sf::RenderWindow& window)
{
	sf::CircleShape shape;
	shape.setOrigin(sf::Vector2f(_radius, _radius));
	shape.setRadius(_radius);
	shape.setFillColor(_color);
	shape.setPosition(_position);
	window.draw(shape);
}

void Bullet::Move(float deltaTime){
	_position = _position + _direction * deltaTime * _speed;
}