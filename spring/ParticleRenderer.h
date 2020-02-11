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
		vector<Colorf> colors;
		vector<Vector4> transforms;

		static Particle* emit(Particle*);
		static Particle* generate();

	public:
		Mesh* mesh;

		unsigned int colorBuffer;
		unsigned int transformBuffer;

		bool playing = true;
		bool runIn2D = false;
		unsigned int maxNumber = 1000;
		unsigned int existingNumber = 0;
		unsigned int shape = 0;

		float lifeTime;

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