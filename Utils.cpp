#include "Utils.h"

sf::Text CreateText(sf::Window& window, sf::Font& font, sf::String text, unsigned int charSize, sf::Text::Style style) 
{
	sf::Text createdText;
	createdText.setFont(font);
	createdText.setString(text);
	createdText.setCharacterSize(charSize);
	createdText.setStyle(style);
	createdText.setOrigin(sf::Vector2f(createdText.getGlobalBounds().width / 2, createdText.getGlobalBounds().height / 2));

	return createdText;
}

sf::Text CreateTextAlone(sf::Window& window, sf::Vector2f position, sf::Font& font, sf::String text, unsigned int charSize, sf::Text::Style style)
{
	sf::Text createdText = CreateText(window, font, text, charSize, style);

	createdText.setPosition(ScalePositionWithScreenSize(window, position));

	return createdText;
}

sf::Text CreateTextChild(sf::Window& window, sf::Vector2f position, sf::Font& font, sf::String text, unsigned int charSize, sf::Text::Style style) 
{
	sf::Text createdText = CreateText(window, font, text, charSize, style);
	createdText.setPosition(position);

	return createdText;
}

sf::Vector2f ScalePositionWithScreenSize(sf::Window& window, sf::Vector2f position) 
{
	float x = (position.x / 1280.0f) * (window.getSize().x);
	float y = (position.y / 720.0f) * (window.getSize().y);
	return sf::Vector2f(x, y);
}