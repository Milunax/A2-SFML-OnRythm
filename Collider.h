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

struct RectangleCollider : public Collider
{
	sf::Vector2f Size;
	float XMin;
	float XMax;
	float YMin;
	float YMax;
};
