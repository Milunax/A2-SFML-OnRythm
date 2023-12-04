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
	if (Distance(circleA.Origin, circleB.Origin) < (circleA.Radius + circleB.Radius)) return true;
	return false;
}

void ClampCircleOutsideCircle(CircleCollider& toClamp, CircleCollider& stayOutside)
{
	float distance = Distance(toClamp.Origin, stayOutside.Origin);

	if (distance < stayOutside.Radius + toClamp.Radius) 
	{
		float angle = atan2(toClamp.Origin.y - stayOutside.Origin.y ,toClamp.Origin.x - stayOutside.Origin.x);
		toClamp.Origin.x = stayOutside.Origin.x + cos(angle) * (stayOutside.Radius + toClamp.Radius);
		toClamp.Origin.y = stayOutside.Origin.y + sin(angle) * (stayOutside.Radius + toClamp.Radius);
	}
}