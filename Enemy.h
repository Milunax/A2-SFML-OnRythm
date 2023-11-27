#pragma once
#include "Entity.h"

class Enemy : public Entity {
	public :
		Enemy(sf::Vector2f startPos, float maxHealth, float speed);
	private :
		Entity* _target;
};