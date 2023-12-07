#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

struct RefsData {
	float deltaTime;
	sf::RenderWindow* window;
	sf::Font* baseFont;
	sf::Clock* frameClock;
	sf::Music* music;
};
