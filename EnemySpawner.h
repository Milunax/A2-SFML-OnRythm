#pragma once
#include <SFML/System/Vector2.hpp>
#include "Player.h"
#include "Enemy.h"
#include <vector>

class EnemySpawner 
{
	public :
		EnemySpawner(sf::Vector2f position);
		Enemy* InstantiateEnemy(Player* enemyTarget);
	private :
		sf::Vector2f _position;
};
