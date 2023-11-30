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