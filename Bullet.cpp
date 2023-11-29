#include "Bullet.h"

Bullet::Bullet(sf::Color color, int radius, sf::Vector2f startPos, sf::Vector2f direction, float speed) {
	_circle.setFillColor(color);
	_circle.setPosition(startPos);
	_circle.setRadius(radius);
	_speed = speed;
}

//void Bullet::Move(float deltaTime){
//	_position.x = _position.x - deltaTime * _speed;
//}