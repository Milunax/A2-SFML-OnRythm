#include "Entity.h"
#include <algorithm>

Entity::Entity(sf::Vector2f startPos, float maxHealth, float speed) {
	_position = startPos;
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

sf::Vector2f Entity::getPosition() {
	return _position;
}

void Entity::setPosition(sf::Vector2f pos) {
	_position = pos;
}