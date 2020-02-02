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
			Colorf color;
			Vector3 size;
			Vector3 position;
			Vector3 eulerangle;
		};

	public:
		ParticleSetting setting;
		Material* material;
		Mesh* mesh;

		Particle();
		void Render();
	};
}