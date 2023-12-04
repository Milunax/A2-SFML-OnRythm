#include "HealthBar.h"

HealthBar::HealthBar(sf::Vector2f startPos, sf::Color color, sf::Vector2f size) {
	_position = startPos;
	_color = color;
	_size = size;
}

void HealthBar::Draw(Data data)
{
	sf::RectangleShape shape;
	shape.setOrigin(_size.x / 2, _size.y / 2);
	shape.setSize(_size);
	shape.setFillColor(_color);
	shape.setPosition(_position);
	data.window->draw(shape);
}

void HealthBar::UpdatePosition(sf::Vector2f newPos) {
	_position = newPos;
}

void HealthBar::UpdateSize(int value) {
	_size.x -= value / 100;
}