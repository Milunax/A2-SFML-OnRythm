#include "Math.h"

float Magnitude(sf::Vector2f vector) 
{
	float magnitude = std::sqrt((vector.x * vector.x) + (vector.y * vector.y));
	return magnitude;
}

void Normalize(sf::Vector2f& vector) 
{
	if (Magnitude(vector) != 0) 
	{
		vector.x = vector.x / Magnitude(vector);
		vector.y = vector.y / Magnitude(vector);
	}
}

float Distance(sf::Vector2f from, sf::Vector2f to) 
{
	sf::Vector2f vectorDistance = to - from;
	float distance = Magnitude(vectorDistance);
	return distance;
}

bool AreCircleCollidersOverlapping(CircleCollider circleA, CircleCollider circleB) 
{
	sf::Vector2 vectorDistance = circleA.Origin - circleB.Origin;
	float distance = Magnitude(vectorDistance);
	if (distance < (circleA.Radius + circleB.Radius)) return true;
	return false;
}