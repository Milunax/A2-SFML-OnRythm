#include "Math.h"

# define PI 3.14159265358979323846

float pi = PI;

float Magnitude(sf::Vector2f vector) 
{
	float magnitude = std::sqrtf((vector.x * vector.x) + (vector.y * vector.y));
	return magnitude;
}

void Normalize(sf::Vector2f& vector) 
{
	float magnitude = Magnitude(vector);

	if(magnitude != 0)
	{
		vector.x = vector.x / magnitude;
		vector.y = vector.y / magnitude;
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

bool IsPointInsideRectangle(sf::Vector2f point, RectangleCollider rectangle) 
{
	return point.x > rectangle.XMin &&
		point.x < rectangle.XMax &&
		point.y > rectangle.YMin &&
		point.y < rectangle.YMax;
}
