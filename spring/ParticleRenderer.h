#pragma once
#include <vector>
#include "springengine.h"
#include "meshrenderer.h"
#include "particle.h"
#include "particleshapemodule.h"

using namespace std;

namespace spring 
{
	class ParticleRenderer : public MeshRenderer
	{
	public:
		static std::vector<ParticleRenderer*> particles;
		static Particle* emit(ParticleRenderer* particleRenderer);

	private:
		vector<Colorf> colors;
		vector<Vector4> transforms;
		vector<Vector4> rotations;

		float emitTimer = 0.0f;
	public:

		unsigned int colorBuffer;
		unsigned int transformBuffer;
		unsigned int rotationBuffer;

		bool playing = true;
		bool runIn2D = false;
		unsigned int maxNumber = 1000;
		unsigned int existingNumber = 0;

		float emitInterval = 10.0f;

		float lifeTime = 5.0f;
		float velocity = 0.0f;
		float size = 1.0f;
		float rotateSpeed = 0.0f;
		ParticleShapeModule* shapeModule;

		std::vector<Particle*> usingParticles;
		std::vector<Particle*> unusedParticles;

		ParticleRenderer();
		ParticleRenderer(Material* material);
		~ParticleRenderer();

		void Play();
		void Pause();
		void Stop();

		static void Update();
		virtual void Init();
		void Render() override;

	// parameters over life
	public:
		bool enableVariableColor = false;
		Colorf beginColor;
		Colorf endColor;

		bool enableVariableVelocity = false;
		float beginVelocity;
		float endVelocity;

		bool enableVariableSize = false;
		float beginSize;
		float endSize;

		bool enableVariableEmitSpeed = false;
		float beginSpeed = 1.0f;
		float endSpeed = 1.0f;

		Colorf getSrcColor(float lifePercent);
		float getSrcVelocity(float lifePercent);
		float getSrcSize(float lifePercent);
		float getEmitInterval(float lifePercent);

	private:
		Colorf colorOverLife(float lifePercent);
		float velocityOverLife(float lifePercent);
		float sizeOverLife(float lifePercent);
	};
}