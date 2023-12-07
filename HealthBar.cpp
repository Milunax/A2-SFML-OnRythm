#include "HealthBar.h"

HealthBar::HealthBar(sf::Vector2f startPos, sf::Color color, sf::Vector2f size) : UIBar(startPos, color, size)
{
}

void HealthBar::UpdateSize(float value, float maxValue) {
	_size.x = (value / maxValue) * _sizeMax.x;
	std::cout << _size.x << std::endl;
	_size.x = std::clamp(_size.x, 0.0f, _sizeMax.x);
}

void HealthBar::Draw(RefsData data) {
	sf::RectangleShape shape;
	shape.setOrigin(_size.x / 2, _size.y / 2);
	shape.setSize(_size);
	shape.setFillColor(_color);
	shape.setPosition(_position);
	data.window->draw(shape);
}