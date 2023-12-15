#include "ParticleSystem.h"
#include "Math.h"
#include "Math.h"

ParticleSystem::ParticleSystem()
{

}

void ParticleSystem::Update(RefsData data)
{
	for (Particle* particle : _allParticles) 
	{
		particle->Update(data.deltaTime);
	}
	EraseOldParticles();
}

void ParticleSystem::EraseOldParticles()
{
	std::vector<Particle*>::iterator it = _allParticles.begin();
	while (it != _allParticles.end())
	{
		if ((*it)->IsOld) 
		{
			delete (*it);
			it = _allParticles.erase(it);
		}
		else 
		{
			it++;
		}
	}
}

void ParticleSystem::Draw(RefsData data)
{
	for (Particle* particle : _allParticles) 
	{
		particle->Draw(*data.window);
	}
}

void ParticleSystem::Explosion(sf::Vector2f position)
{
	float angle = 0;
	float angleIncrement = 360.0f / 22;

	for (int i = 0; i < 22; i++)
	{
		sf::Vector2f direction = sf::Vector2f(cos(angle), sin(angle));
		Normalize(direction);
		Particle* newParticle = new Particle(_redParticle, position, direction);
		_allParticles.push_back(newParticle);
		angle += angleIncrement;
	}
}