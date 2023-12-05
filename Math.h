#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include "Collider.h"

float Magnitude(sf::Vector2f vector);
void Normalize(sf::Vector2f& vector);
float Distance(sf::Vector2f from, sf::Vector2f to);
bool AreCircleCollidersOverlapping(CircleCollider colliderA, CircleCollider colliderB);
void ClampCircleOutsideCircle(CircleCollider& toClamp, CircleCollider& stayOut);
bool IsPointInsideRectangle(sf::Vector2f point, RectangleCollider rectangle);
