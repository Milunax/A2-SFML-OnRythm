#pragma once
#include <SFML/System/Vector2.hpp>
#include "Player.h"
#include "Enemy.h"
#include <vector>

class EnemySpawner 
{
	public :
		EnemySpawner(sf::Vector2f position);
		Enemy* InstantiateEnemy(EnemyData data, sf::Vector2f position, Player* enemyTarget);
		sf::Vector2f GetPosition();
	private :
		sf::Vector2f _position;
};
