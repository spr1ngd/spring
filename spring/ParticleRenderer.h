#pragma once
#include <vector>
#include "springengine.h"
#include "meshrenderer.h"
#include "particle.h"

using namespace std;

namespace spring 
{
	class ParticleRenderer : public MeshRenderer
	{
	public:
		static std::vector<ParticleRenderer*> particles;

	private:
		// 1. generate particle( with properties : lifetime/color/velocity/acceleration/size/emit shape etc...)
		// 2. over life time , recycle particles and regenerate it
		// 3. random particle properties
		// 4. use particle shader render it
		bool playing = true;

		static Particle* emit(Particle*);
		static Particle* generate();

	public:
		bool runIn2D = false;
		unsigned int maxNumber = 1000;
		unsigned int existingNumber = 0;
		unsigned int shape = 0;

		std::vector<Particle*> usingParticles;
		std::vector<Particle*> unusedParticles;

		ParticleRenderer();
		ParticleRenderer(Material* material);
		~ParticleRenderer();

		void Play();
		void Pause();
		void Stop();

		static void Update(); // call this method per frame.

		virtual void Init();
		void Render() override;
	};
}