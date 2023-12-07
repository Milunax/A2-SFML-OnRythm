#include "ExperienceBar.h"


ExperienceBar::ExperienceBar(sf::Vector2f startPos, sf::Color color, sf::Vector2f size) : UIBar(startPos, color, size)
{
	_size.x = 0;
	_experienceBarBackground = new UIBar(startPos, sf::Color::Black, sf::Vector2f(1000, 20));
	_font.loadFromFile("../Assets/ARIAL.TTF");
	_levelText.setFont(_font);
	_levelText.setString("Lvl. 1");
	_levelText.setCharacterSize(16);
	_levelText.setStyle(sf::Text::Bold);
	_levelText.setPosition(sf::Vector2f(_position. x - _sizeMax.x / 2, _position.y / 2));
}

void ExperienceBar::Draw(Data data)
{
	_experienceBarBackground->Draw(data);

	sf::RectangleShape shape;
	shape.setOrigin(_experienceBarBackground->GetSizeMax().x / 2, _size.y / 2);
	shape.setSize(_size);
	shape.setFillColor(_color);
	shape.setPosition(_position);
	data.window->draw(shape);
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