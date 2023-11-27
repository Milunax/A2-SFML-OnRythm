#include "Entity.h"
#include <algorithm>

Entity::Entity(float maxHealth, float speed) {
	_maxHealth = maxHealth;
	_health = _maxHealth;
	_speed = speed;
}

void Entity::TakeDamage(float damage) {
	_health = std::clamp(_health - damage, 0.0f, _maxHealth);
}

void Entity::Heal(float heal) {
	_health = std::clamp(_health + heal, 0.0f, _maxHealth);
}