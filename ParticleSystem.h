#pragma once
#include <vector>
#include "Particle.h"


class ParticleSystem
{
	public:
		ParticleSystem();
		void Update();
		void Explosion();
	private:
		std::vector<Particle*> _allParticles;
};