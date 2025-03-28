#include "Button.h"

ButtonData basicButton = {sf::Vector2f(200, 50), sf::Color::Transparent, sf::Color::White, 5.0f};

Button::Button(ButtonData buttonData, RefsData data, sf::Vector2f position, sf::String text)
{
	_size = buttonData.Size;
	_color = buttonData.Color;
	_outlineColor = buttonData.OutlineColor;
	_outlineThickness = buttonData.OutlineThickness;
	_position = ScalePositionWithScreenSize(*data.window, position);

	_textFont = *data.baseFont;
	_text = text;
}

RectangleCollider Button::GetCollider() 
{
	float xMin = _position.x - (_size.x / 2);
	float xMax = _position.x + (_size.x / 2);
	float yMin = _position.y - (_size.y / 2);
	float yMax = _position.y + (_size.y / 2);
	RectangleCollider collider = {_position, _size, xMin, xMax, yMin, yMax};
	return collider;
}

void Button::SetText(sf::String text) 
{
	_text = text;
}

void Button::Draw(RefsData data) 
{
	sf::RectangleShape shape;
	shape.setSize(_size);
	shape.setOrigin(sf::Vector2f(_size.x / 2.0f, _size.y / 2.0f));
	shape.setFillColor(_color);
	shape.setOutlineColor(_outlineColor);
	shape.setOutlineThickness(_outlineThickness);
	shape.setPosition(_position);
	data.window->draw(shape);
	
	sf::Text buttonText = CreateTextChild(*data.window, _position, _textFont, _text, 24, sf::Text::Bold);

	data.window->draw(buttonText);
}