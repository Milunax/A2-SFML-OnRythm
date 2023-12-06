#include "ExperienceBar.h"

ExperienceBar::ExperienceBar(sf::Vector2f startPos, sf::Color color, sf::Vector2f size) : UIBar(startPos, color, size)
{
	_size.x = 0;
	_experienceBarBackground = new UIBar(sf::Vector2f(640, 20), sf::Color::Black, sf::Vector2f(1000, 20));
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
