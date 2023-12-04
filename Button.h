#pragma once
#include <SFML/Graphics.hpp>
#include "Data.h"
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
		Button(ButtonData buttonData, sf::Vector2f position, sf::Text buttonText);
		void Draw(Data data);
	private:
		sf::Vector2f _size;
		sf::Color _color;
		sf::Color _outlineColor;
		float _outlineThickness;
		sf::Vector2f _position;

		sf::Text _buttonText;
};
