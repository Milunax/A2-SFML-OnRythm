#pragma once
#include <SFML/Graphics.hpp>
#include "RefsData.h"
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
		Button(ButtonData buttonData, RefsData data, sf::Vector2f position, sf::String text);
		RectangleCollider GetCollider();
		void SetText(sf::String text);
		void Draw(RefsData data);
	private:
		sf::Vector2f _size;
		sf::Color _color;
		sf::Color _outlineColor;
		float _outlineThickness;
		sf::Vector2f _position;

		sf::Font _textFont;
		sf::String _text;
};
