#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window.hpp>
#include "RefsData.h"

class UIBar {
	public:
		UIBar(sf::Vector2f startPos, sf::Color color, sf::Vector2f size);
		virtual void Draw(RefsData data);
		void UpdatePosition(sf::Vector2f newPos);
		virtual void UpdateSize(int value, int maxValue);
		sf::Vector2f GetSizeMax();
	protected: 
		sf::Vector2f _position;
		sf::Color _color;
		sf::Vector2f _sizeMax;
		sf::Vector2f _size;
	private:
};