#include "Entity.h"
#include <algorithm>

Entity::Entity(sf::Vector2f startPos, float maxHealth, float speed) {
	_position = startPos;
	_maxHealth = maxHealth;
	_health = _maxHealth;
	_speed = speed;
	IsAlive = true;
	HasTakenDamage = false;
	_damageTakenToShow = 0;
}

void Entity::TakeDamage(float damage) {
	_health = std::clamp(_health - damage, 0.0f, _maxHealth);
	HasTakenDamage = true;
	_damageTakenToShow += damage;


	if (_health <= 0) 
	{
		Die();
	}
}

float Entity::GetDamageTaken()
{
	return _damageTakenToShow;
}

void Entity::Heal(float heal) {
	_health = std::clamp(_health + heal, 0.0f, _maxHealth);
}

void Entity::Die() 
{
	IsAlive = false;
}

void Entity::Draw(sf::RenderWindow& window) 
{

}

sf::Vector2f Entity::GetPosition() {
	return _position;
}

void Entity::SetPosition(sf::Vector2f pos) {
	_position = pos;
}

int Entity::GetSpeed() {
	return _speed;
}