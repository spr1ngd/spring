#include "particle.h"

using namespace spring;

Particle::Particle() 
{
	this->setting = ParticleSetting();
	this->setting.color = Colorf::white;
	this->setting.size = 1.0f;
}