#pragma once
#include <SFML/System/Vector2.hpp>
#include "Enemy.h"

class EnemySpawner 
{
	public :
		EnemySpawner(sf::Vector2f position);
		Enemy* InstantiateEnemy(Entity* enemyTarget);
	private :
		sf::Vector2f _position;
};
