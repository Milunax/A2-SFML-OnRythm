#pragma once
#include <SFML/Graphics.hpp>
#include "Data.h"
#include"Collider.h"
#include "Utils.h"

struct ButtonData 
{
	sf::Vector2f Size;
	sf::Color Color;
	sf::Color OutlineColor;
	float OutlineThickness;

};

extern ButtonData basicButton;

class Button
{
	public:
		Button(ButtonData buttonData, sf::Vector2f position, sf::Font textFont, sf::String text);
		RectangleCollider GetCollider();
		void Draw(Data data);
	private:
		sf::Vector2f _size;
		sf::Color _color;
		sf::Color _outlineColor;
		float _outlineThickness;
		sf::Vector2f _position;

		sf::Font _textFont;
		sf::String _text;
};
