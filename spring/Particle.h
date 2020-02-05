#pragma once 
#include "springengine.h"

namespace spring 
{
	class Particle
	{
	public:
		struct ParticleSetting
		{
			float lifeTime;
			float existingTime;
			float velocity;
			float acceleration;
			float size;
			Colorf color;
			Vector3 position;
			Vector3 eulerangle;
		};

	public:
		ParticleSetting setting;

		Particle();
	};
}