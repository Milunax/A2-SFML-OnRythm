#pragma once
#include "UIBar.h"

class ExperienceBar : public UIBar{
	public:
		ExperienceBar(sf::Vector2f startPos, sf::Color color, sf::Vector2f size);
		void Draw(RefsData data);
		void UpdateSize(int value, int maxValue);
		void ResetSize();
	private:
		UIBar* _experienceBarBackground;
};
