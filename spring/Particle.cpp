#include "particle.h"

using namespace spring;

Particle::Particle() 
{
	this->setting = ParticleSetting();

	this->setting.size = Vector3::one;
}

void Particle::Render() 
{

}