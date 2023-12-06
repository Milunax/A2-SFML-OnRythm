#include "HealthBar.h"

HealthBar::HealthBar(sf::Vector2f startPos, sf::Color color, sf::Vector2f size) : UIBar(startPos, color, size)
{
}

void HealthBar::UpdateSize(int value, int maxValue) {
	_size.x = ((float)value / maxValue) * _sizeMax.x;
	std::cout << _size.x << std::endl;
	_size.x = std::clamp(_size.x, 0.0f, _sizeMax.x);
}