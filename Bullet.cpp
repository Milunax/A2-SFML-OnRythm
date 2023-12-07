#include "Bullet.h"



Bullet::Bullet(sf::Color color, float radius, sf::Vector2f startPos, sf::Vector2f direction, float speed, float damage) 
{
	_color = color;
	_position = startPos;
	_radius = radius;
	_speed = speed;
	_direction = direction;
	Normalize(_direction);
	_damage = damage;
}

void Bullet::Draw(sf::RenderWindow& window)
{
	sf::CircleShape shape;
	shape.setOrigin(sf::Vector2f(_radius, _radius));
	shape.setRadius(_radius);
	shape.setFillColor(_color);
	shape.setPosition(_position);
	window.draw(shape);
}

void Bullet::Move(float deltaTime)
{
	_position = _position + _direction * deltaTime * _speed;
}

bool Bullet::IsBulletOutOfWindow(RefsData data) 
{
	if (_position.x < -50 || _position.x > data.window->getSize().x + 50 || _position.y < -50 || _position.y > data.window->getSize().y + 50) 
	{
		return true;
	}
	return false;
}

void Bullet::CheckPosition(RefsData data, std::vector<Bullet*>& bulletList) 
{
	std::vector<Bullet*>::iterator it = bulletList.begin();
	while (it != bulletList.end()) {
		if ((*it)->IsBulletOutOfWindow(data))
		{
			Bullet* bulletToDelete = (*it);
			it = bulletList.erase(it);
			delete bulletToDelete;
		}
		else
		{
			it++;
		}
	}
}

CircleCollider Bullet::GetCollider()
{
	CircleCollider collider = { _position, _radius };
	return collider;
}

float Bullet::GetDamage() {
	return _damage;
}
