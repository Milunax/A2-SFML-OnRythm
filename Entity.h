#pragma once

class Entity 
{
	public :
		Entity(float maxHealth, float speed);
		void TakeDamage(float damage);
		void Heal(float heal);
	private : 
		float _maxHealth;
		float _health;
		float _speed;
};