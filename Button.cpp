#include "Button.h"

ButtonData basicButton = {sf::Vector2f(200, 50), sf::Color::Transparent, sf::Color::White, 5.0f};

Button::Button(ButtonData buttonData, sf::Vector2f position, sf::Text buttonText)
{
	_size = buttonData.Size;
	_color = buttonData.Color;
	_outlineColor = buttonData.OutlineColor;
	_outlineThickness = buttonData.OutlineThickness;
	_position = position;

	_buttonText = buttonText;
}

void Button::Draw(Data data) 
{
	sf::RectangleShape shape;
	shape.setSize(_size);
	shape.setOrigin(sf::Vector2f(_size.x / 2.0f, _size.y / 2.0f));
	shape.setFillColor(_color);
	shape.setOutlineColor(_outlineColor);
	shape.setOutlineThickness(_outlineThickness);
	shape.setPosition(_position);
	data.window->draw(shape);

	data.window->draw(_buttonText);
}