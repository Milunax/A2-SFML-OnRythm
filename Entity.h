#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

class Entity 
{
	public :
		Entity(sf::Vector2f startPos, float maxHealth, float speed);
		virtual void TakeDamage(float damage);
		bool HasTakenDamage;
		float GetDamageTaken();
		void ResetDamageTaken();
		void Heal(float heal);
		virtual void Die();
		bool IsAlive;
		virtual void Draw(sf::RenderWindow& window);
		sf::Vector2f GetPosition();
		void SetPosition(sf::Vector2f pos);
		int GetSpeed();
	protected:
		float _speed;
		sf::Vector2f _position;
		float _health;
		float _maxHealth;
		float _damageTakenToShow;
	private : 
		
		
};