#include "particlerenderer.h"

using namespace spring;

std::vector<ParticleRenderer*> ParticleRenderer::particles;

ParticleRenderer::ParticleRenderer() 
{
	Shader* particle = Shader::Load("particle/particle.vs","particle/particle.fs");
	Material* particleMaterial = new Material(particle);
	this->material = particleMaterial;
}

ParticleRenderer::ParticleRenderer(Material* material) 
{
	this->material = material;
}

ParticleRenderer::~ParticleRenderer()
{
	// todo : destroy material & shader program instance
}

#pragma region particle life cycle

void ParticleRenderer::Play() 
{
	this->playing = true;
}

void ParticleRenderer::Pause() 
{
	this->playing = false;
}

void ParticleRenderer::Stop() 
{
	this->playing = false;
	// clear all particles status 
	// clear all particles properties
}

void ParticleRenderer::Update() 
{
	if (!this->playing)
		return;

	// if exist particle number less equal maxNumber -> generate new particle and add new particle to using particles array
	// else update particles and calculate particle life time 
	// -> if particle existing time greater than life time , recycle particle to unused paritcles array
	if (this->existingNumber < this->maxNumber) 
	{
		// generate 
		Particle* particle = this->generate();
		// emit it with additional particle properties ( velocity/color/size ...... )
		particle = this->emit(particle);
	}
	else 
	{
		// calculate all particles life cycle , and playing particles physical motion
	}
}

#pragma endregion

#pragma region particles emitter and generator

ParticleRenderer::Particle* ParticleRenderer::emit(Particle*)
{
	// todo : generate random particle properties
}

ParticleRenderer::Particle* ParticleRenderer::generate()
{
	// todo : generate mesh data (contains vertex data / texcoord)
}

#pragma endregion



void ParticleRenderer::Init() 
{

}

void ParticleRenderer::Render() 
{

}