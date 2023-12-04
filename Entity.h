#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

class Entity 
{
	public :
		Entity(sf::Vector2f startPos, float maxHealth, float speed);
		virtual void TakeDamage(float damage);
		void Heal(float heal);
		virtual void Draw(sf::RenderWindow& window);
		sf::Vector2f GetPosition();
		void SetPosition(sf::Vector2f pos);
		int GetSpeed();
	protected:
		float _speed;
		sf::Vector2f _position;
		float _health;
	private : 
		float _maxHealth;
		
};