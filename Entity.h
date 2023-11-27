#pragma once
#include <SFML/System/Vector2.hpp>

class Entity 
{
	public :
		Entity(sf::Vector2f startPos, float maxHealth, float speed);
		void TakeDamage(float damage);
		void Heal(float heal);
	private : 
		sf::Vector2f _position;

		float _maxHealth;
		float _health;
		float _speed;

};