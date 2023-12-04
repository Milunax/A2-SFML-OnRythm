#pragma once
#include <SFML/Graphics.hpp>
#include "Data.h"

class HealthBar {
	public:
		HealthBar(sf::Vector2f startPos, sf::Color color, sf::Vector2f size);
		void Draw(Data data);
		void UpdatePosition(sf::Vector2f newPos);
		void UpdateSize(int value);
	private:
		sf::Vector2f _position;
		sf::Color _color;
		sf::Vector2f _sizeMax;
		sf::Vector2f _size;
};