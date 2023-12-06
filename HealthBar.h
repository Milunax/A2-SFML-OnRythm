#pragma once
#include "UIBar.h"
#include <SFML/Graphics.hpp>
#include "Data.h"

class HealthBar : public UIBar {
	public:
		HealthBar(sf::Vector2f startPos, sf::Color color, sf::Vector2f size);
		void UpdateSize(int value);
	private:
		sf::Vector2f _position;
		sf::Color _color;
		sf::Vector2f _sizeMax;
		sf::Vector2f _size;
};