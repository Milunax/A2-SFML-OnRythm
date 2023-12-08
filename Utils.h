#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

sf::Text CreateText(sf::Window& window, sf::Font& font, sf::String text = "Default", unsigned int charSize = 24, sf::Text::Style style = sf::Text::Regular);
sf::Text CreateTextAlone(sf::Window& window, sf::Vector2f position, sf::Font& font, sf::String text = "Default", unsigned int charSize = 24, sf::Text::Style style = sf::Text::Regular);
sf::Text* CreateTextAtPosition(sf::Window& window, sf::Vector2f position, sf::Font& font, sf::String text = "Default", unsigned int charSize = 24, sf::Text::Style style = sf::Text::Regular);
sf::Text CreateTextChild(sf::Window& window, sf::Vector2f position, sf::Font& font, sf::String text = "Default", unsigned int charSize = 24, sf::Text::Style style = sf::Text::Regular);

sf::Vector2f ScalePositionWithScreenSize(sf::Window& window, sf::Vector2f position);

std::string IntStringConcatenate(int value, std::string text);