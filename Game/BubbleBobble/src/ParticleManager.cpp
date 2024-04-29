#include "ParticleManager.h"

ParticleManager::ParticleManager()
{
}
ParticleManager::~ParticleManager()
{
}
AppStatus ParticleManager::Initialise()
{
	//Nothing needs to be done because the texture is located within the enemy sprites
	//and loaded by the EnemyManager

	return AppStatus::OK;
}
void ParticleManager::Add(const Point& pos)
{
	bool found = false;
	for (Particle& particle : particles)
	{
		if (!particle.IsAlive())
		{
			particle.Init(pos);
			found = true;
			break;
		}
	}
	if (!found) LOG("Not enough space to add a new particle in the ParticleManager!");
}
void ParticleManager::Clear()
{
	for (Particle& particle : particles)
		particle.SetAlive(false);
}
void ParticleManager::Update()
{
	bool animation_complete;

	for (Particle& particle : particles)
	{
		if (particle.IsAlive())
		{
			//Update animation
			animation_complete = particle.Update();

			if (animation_complete)
				particle.SetAlive(false);
		}
	}
}
void ParticleManager::Draw() const
{
	//Iterate over the particles vector by reference instead of by value to avoid a copy
	//of each Entity object
	for (const Particle& particle : particles)
		if (particle.IsAlive())	particle.Draw();
}
