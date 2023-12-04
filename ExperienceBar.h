#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"

class ExperienceBar {
	public:
		ExperienceBar();
	private:
		Player _player;
		sf::Vector2f _position;
		sf::Color _color;
		sf::Vector2f _size;
};
