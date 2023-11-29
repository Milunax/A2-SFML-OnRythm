#pragma once
#include "Entity.h"
#include <SFML/Graphics.hpp>

class Player : public Entity {
	public :
		Player(sf::Color color, sf::Vector2f startPos, int radius, float maxHealth, float speed);
		sf::CircleShape& GetPlayerShape();

	private :
		sf::CircleShape _circle;
};
