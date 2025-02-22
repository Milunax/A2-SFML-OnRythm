#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include "Math.h"
#include "RefsData.h"
#include "Collider.h"

class Bullet {
	public :
		Bullet(sf::Color color, float radius, sf::Vector2f startPos, sf::Vector2f direction, float speed, float damage);
		void Draw(sf::RenderWindow& window);
		void Move(float deltaTime);
		bool IsBulletOutOfWindow(RefsData data);
		void CheckPosition(RefsData data, std::vector<Bullet*>& bulletList);
		CircleCollider GetCollider();
		float GetDamage();
	private :
		sf::CircleShape _circle;
		float _radius;
		sf::Color _color;
		float _speed;
		sf::Vector2f _position;
		sf::Vector2f _direction;
		float _damage;
};
