#include "Particle.h"

ParticleData _redParticle = { sf::Vector2f(6,6), sf::Color::Red, 100.0f ,0.3f};

Particle::Particle(ParticleData particleData, sf::Vector2f startPos, sf::Vector2f direction)
{
	_size = particleData.Size;
	_color = particleData.Color;
	_position = startPos;
	_direction = direction;
	_speed = particleData.Speed;

	_lifeTime = 0;
	_lifeSpan = particleData.LifeSpan;
	IsOld = false;
}

void Particle::Update(float deltaTime)
{
	_lifeTime += deltaTime;
	if (_lifeTime >= _lifeSpan) 
	{
		IsOld = true;
	}
	Move(deltaTime);
}

void Particle::Move(float deltaTime)
{
	_position = _position + _direction * _speed * deltaTime;
}

void Particle::Draw(sf::RenderWindow& window) 
{
	sf::RectangleShape shape;
	shape.setSize(_size);
	shape.setFillColor(_color);
	shape.setOrigin(sf::Vector2f(_size.x / 2, _size.y / 2));
	shape.setPosition(_position);

	window.draw(shape);
}