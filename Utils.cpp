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

	float createdTextX = (640.0f / 1280.0f) * window.getSize().x;
	float createdTextY = (100.0f / 720.0f) * window.getSize().y;
	createdText.setPosition(sf::Vector2f(createdTextX, createdTextY));

	return createdText;
}

sf::Text CreateTextButton(sf::Window& window, sf::Vector2f position, sf::Font& font, sf::String text, unsigned int charSize, sf::Text::Style style) 
{
	sf::Text createdText = CreateText(window, font, text, charSize, style);
	createdText.setPosition(position);

	return createdText;
}