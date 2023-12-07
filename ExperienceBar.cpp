#include "ExperienceBar.h"


ExperienceBar::ExperienceBar(sf::Vector2f startPos, sf::Color color, sf::Vector2f size) : UIBar(startPos, color, size)
{
	_size.x = 0;
	_experienceBarBackground = new UIBar(startPos, sf::Color::Black, sf::Vector2f(1000, 20));
}

void ExperienceBar::Draw(RefsData data)
{
	_experienceBarBackground->Draw(data);

	sf::RectangleShape shape;
	shape.setOrigin(_experienceBarBackground->GetSizeMax().x / 2, _size.y / 2);
	shape.setSize(_size);
	shape.setFillColor(_color);
	sf::Vector2f scaledPosition = ScalePositionWithScreenSize((*data.window), _position);
	shape.setPosition(scaledPosition);
	data.window->draw(shape);

	_levelText = CreateTextChild((*data.window), sf::Vector2f(scaledPosition.x, scaledPosition.y), (*data.baseFont), "Lvl. 1", 16);
	data.window->draw(_levelText);
}

void ExperienceBar::UpdateSize(int value, int maxValue)
{
	_size.x += ((value * _sizeMax.x) / maxValue) ;
	_size.x = std::clamp(_size.x, 0.0f, _sizeMax.x);
}

void ExperienceBar::ResetSize() 
{
	_size.x = 0;
}

void ExperienceBar::UpdateLevelText(int level) {
	std::string result;
	std::stringstream str;
	str << "Lvl. " << level;
	result = str.str();
	_levelText.setString(result);
}