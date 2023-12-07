#include "UIBar.h"

UIBar::UIBar(sf::Vector2f startPos, sf::Color color, sf::Vector2f size)
{
	_position = startPos;
	_color = color;
	_size = size;
	_sizeMax = size;
}

void UIBar::Draw(RefsData data)
{
	sf::RectangleShape shape;
	shape.setOrigin(_size.x / 2, _size.y / 2);
	shape.setSize(_size);
	shape.setFillColor(_color);
	sf::Vector2f scaledPosition = ScalePositionWithScreenSize((*data.window), _position);
	shape.setPosition(scaledPosition);
	data.window->draw(shape);
}

void UIBar::UpdatePosition(sf::Vector2f newPos)
{
	_position = newPos;
}

void UIBar::UpdateSize(int value, int maxValue)
{
}

sf::Vector2f UIBar::GetSizeMax()
{
	return _sizeMax;
}
