#pragma once
#include "UIBar.h"
#include <iostream>
#include <sstream>

class ExperienceBar : public UIBar{
	public:
		ExperienceBar(sf::Vector2f startPos, sf::Color color, sf::Vector2f size);
		void Draw(Data data);
		void UpdateSize(int value, int maxValue);
		void ResetSize();
		void UpdateLevelText(int level);
	private:
		UIBar* _experienceBarBackground;
		sf::Font _font;
		sf::Text _levelText;
};
