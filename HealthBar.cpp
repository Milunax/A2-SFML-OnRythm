#include "HealthBar.h"

HealthBar::HealthBar(sf::Vector2f startPos, sf::Color color, sf::Vector2f size) : UIBar(startPos, color, size)
{
}

void HealthBar::UpdateSize(int value) {
	_size.x -= value;
	_size.x = std::clamp(_size.x, 0.0f, _sizeMax.x);
}