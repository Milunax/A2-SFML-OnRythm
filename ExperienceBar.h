#pragma once
#include "UIBar.h"
#include <iostream>
#include <sstream>
#include "Utils.h"

class ExperienceBar : public UIBar{
	public:
		ExperienceBar(sf::Vector2f startPos, sf::Color color, sf::Vector2f size);
		void Draw(RefsData data);
		void UpdateSize(int value, int maxValue);
		void ResetSize();
		void UpdateLevel(int level);
		std::string GetLevelText(int level);
	private:
		UIBar* _experienceBarBackground;
		sf::Text _levelText;
		sf::Vector2f _scaledPosition;
		int _playerLevel = 1;
};
