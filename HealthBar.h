#pragma once
#include "UIBar.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "RefsData.h"

class HealthBar : public UIBar {
	public:
		HealthBar(sf::Vector2f startPos, sf::Color color, sf::Vector2f size);
		void UpdateSize(float value, float maxValue);
	private:
};