#pragma once
#include <SFML/System/Vector2.hpp>

struct Collider
{
	sf::Vector2f Origin;
};

struct CircleCollider : public Collider
{
	float Radius;
};
