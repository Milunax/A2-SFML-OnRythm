#pragma once
#include <SFML/Graphics.hpp>

struct ParticleData
{
	sf::Vector2f Size;
	sf::Color Color;

	float Speed;

	float LifeSpan;
};

extern ParticleData _redParticle;

class Particle 
{
	public:
		Particle(ParticleData particleData, sf::Vector2f startPos, sf::Vector2f direction);
		void Update(float deltaTime);
		void Move(float deltaTime);
		void Draw(sf::RenderWindow& window);
		bool IsOld;
	private:
		sf::Vector2f _size;
		sf::Color _color;
		sf::Vector2f _position;
		sf::Vector2f _direction;
		float _speed;

		float _lifeTime;
		float _lifeSpan;
};