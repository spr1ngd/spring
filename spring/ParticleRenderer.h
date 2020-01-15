#pragma once
#include <vector>
#include "springengine.h"
#include "meshrenderer.h"

using namespace std;

namespace spring 
{
	class ParticleRenderer : public MeshRenderer
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

		class Particle 
		{
		public:
			ParticleSetting setting;
		};

		static std::vector<ParticleRenderer*> particles;
	private:
		// 1. generate particle( with properties : lifetime/color/velocity/acceleration/size/emit shape etc...)
		// 2. over life time , recycle particles and regenerate it
		// 3. random particle properties
		// 4. use particle shader render it
		bool playing = true;

		Particle* emit(Particle*);
		Particle* generate();

	public:
		bool runIn2D = false;
		unsigned int maxNumber = 1000;
		unsigned int existingNumber = 200;
		unsigned int shape = 0;

		std::vector<Particle*> usingParticles;
		std::vector<Particle*> unusedParticles;

		ParticleRenderer();
		ParticleRenderer(Material* material);
		~ParticleRenderer();

		void Play();
		void Pause();
		void Stop();
		void Update(); // call this method per frame.

		virtual void Init();
		void Render() override;
	};
}