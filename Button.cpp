#include "Button.h"

ButtonData basicButton = {sf::Vector2f(200, 50), sf::Color::Transparent, sf::Color::White, 5.0f};

Button::Button(ButtonData buttonData, sf::Vector2f position, sf::Font textFont, sf::String text)
{
	_size = buttonData.Size;
	_color = buttonData.Color;
	_outlineColor = buttonData.OutlineColor;
	_outlineThickness = buttonData.OutlineThickness;
	_position = position;

	_textFont = textFont;
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

void Button::Draw(Data data) 
{
	sf::RectangleShape shape;
	shape.setSize(_size);
	shape.setOrigin(sf::Vector2f(_size.x / 2.0f, _size.y / 2.0f));
	shape.setFillColor(_color);
	shape.setOutlineColor(_outlineColor);
	shape.setOutlineThickness(_outlineThickness);
	
	float x = (_position.x / 1280.0f) * (data.window->getSize().x);
	float y = (_position.y / 720.0f) * (data.window->getSize().y);
	sf::Vector2f scaledPosition = sf::Vector2f(x, y);
	shape.setPosition(scaledPosition);
	data.window->draw(shape);
	
	sf::Text buttonText = CreateTextButton(*data.window, scaledPosition, _textFont, _text, 24, sf::Text::Bold);

	data.window->draw(buttonText);
}