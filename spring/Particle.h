#pragma once 
#include "springengine.h"

namespace spring 
{
	class Particle
	{
	public:
		struct ParticleSetting
		{
			float lifeTime = 5.0f;
			float existingTime = 0.0f;
			float velocity = 1.0f;
			float acceleration = 0.0f;
			float size = 1.0f;
			Colorf color;
			Vector3 position;
			Vector3 eulerangle;
			Vector4 rotation;
			Vector3 direction;
		};

	public:
		ParticleSetting setting;

		Particle();
		~Particle();
	};
}