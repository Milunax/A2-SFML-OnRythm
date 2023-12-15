#pragma once
#include <vector>
#include "Particle.h"
#include "RefsData.h"


class ParticleSystem
{
	public:
		ParticleSystem();
		void Update(RefsData data);
		void EraseOldParticles();
		void Draw(RefsData data);
		void Explosion(sf::Vector2f position);
	private:
		std::vector<Particle*> _allParticles;
};