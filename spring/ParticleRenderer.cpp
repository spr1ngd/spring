#include "particlerenderer.h"
#include "particle.h"
#include "primitive.h"
#include "springengine.h"

using namespace std;
using namespace spring;

std::vector<ParticleRenderer*> ParticleRenderer::particles;

ParticleRenderer::ParticleRenderer() 
{
	this->shapeModule = new ParticleShapeModule(this->transform);
	Shader* particle = Shader::Load("particle/particle.vs","particle/particle.fs");
	Material* particleMaterial = new Material(particle);
	this->material = particleMaterial;
	this->Init();
	particles.push_back(this);
}

ParticleRenderer::ParticleRenderer(Material* material) 
{
	this->shapeModule = new ParticleShapeModule(this->transform);
	this->material = material;
	this->Init();
	particles.push_back(this);
}

ParticleRenderer::~ParticleRenderer()
{
	delete this->shapeModule;
	for (auto item = particles.begin(); item != particles.end(); item++) 
	{
		if (*item == this)
		{
			particles.erase(item);
			return;
		}
	}
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
}

void ParticleRenderer::Update() 
{
	for (ParticleRenderer* particleRenderer : particles) 
	{
		if (!particleRenderer->playing)
			return;
		particleRenderer->emitTimer += Timer::deltaTime;

		// particle life circle and physical simulation 

		int index = 0;
		for (vector<Particle*>::iterator item = particleRenderer->usingParticles.begin(); item != particleRenderer->usingParticles.end(); item++, index++)
		{
			Particle* alivePartice = *item;
			alivePartice->setting.existingTime += Timer::deltaTime;
			float lifePercent = alivePartice->setting.existingTime / alivePartice->setting.lifeTime;

			alivePartice->setting.velocity = particleRenderer->getSrcVelocity(lifePercent);
			alivePartice->setting.color = particleRenderer->getSrcColor(lifePercent);
			alivePartice->setting.size = particleRenderer->getSrcSize(lifePercent);

			// update color
			particleRenderer->colors[index] = alivePartice->setting.color;

			// update position / direction
			alivePartice->setting.position += alivePartice->setting.direction * Timer::deltaTime * alivePartice->setting.velocity;
			particleRenderer->transforms[index] = Vector4(alivePartice->setting.position.x, alivePartice->setting.position.y, alivePartice->setting.position.z, alivePartice->setting.size);

			// update rotation
			particleRenderer->rotations[index].y += Timer::deltaTime * particleRenderer->rotateSpeed;

			// update existing time;
			if (alivePartice->setting.existingTime > alivePartice->setting.lifeTime)
			{ 
				item = particleRenderer->usingParticles.erase(item);
				particleRenderer->existingNumber--;
				delete alivePartice;
				if( item == particleRenderer->usingParticles.end())
					break;
			}
		}

		// emit particles
		float emitInterval = particleRenderer->getEmitInterval(0.0f);
		// calculate emit count
		unsigned int emitCount = (int)(particleRenderer->emitTimer / emitInterval);
		if (emitCount > 0)
		{
			if (particleRenderer->existingNumber < particleRenderer->maxNumber)
			{
				unsigned int remainCount = particleRenderer->maxNumber - particleRenderer->existingNumber;
				if (emitCount > remainCount)
					emitCount = remainCount;
				for (unsigned int index = 0; index < emitCount; index++)
				{
					Particle* particle = emit(particleRenderer);
					particleRenderer->usingParticles.push_back(particle);
					particleRenderer->existingNumber++;
				}
			}
			particleRenderer->emitTimer = 0.0f;
		}
	}
}

#pragma endregion

#pragma region particles emitter and generator

Particle* ParticleRenderer::emit(ParticleRenderer* particleRenderer)
{
	Particle* particle = new Particle();
	// todo : replaced those code use particle shape module object.
	Vector3 position, direction;
	particleRenderer->shapeModule->getSrcParticle(position, direction);

	particle->setting.existingTime = 0.0f;
	particle->setting.lifeTime = particleRenderer->lifeTime;
	float lifePercent = particle->setting.existingTime / particle->setting.lifeTime;

	particle->setting.velocity = particleRenderer->getSrcVelocity(lifePercent);// static_cast<float>(Mathf::Randomf(4.0f, 8.0f))* particleRenderer->velocity;
	particle->setting.color = particleRenderer->getSrcColor(lifePercent);//Color::white;
	particle->setting.size = particleRenderer->getSrcSize(lifePercent);//static_cast<float>(Mathf::Randomf(1.0f, 3.0f)) * particleRenderer->size;

	particle->setting.position = position;// Vector3(Mathf::Randomf(-100.0f, 100.0f), Mathf::Randomf(-50.0f, 50.0f), Mathf::Randomf(-100.0f, 100.0f));
	particle->setting.direction = direction;

	// update shader uniform buffer data
	particleRenderer->colors.push_back(Colorf::white);
	particleRenderer->transforms.push_back(Vector4(particle->setting.position.x, particle->setting.position.y, particle->setting.position.z, particle->setting.size));
	particleRenderer->rotations.push_back(Vector4(0.0f, 0.0f, 0.0f, 0.0f));
	return particle;
}

#pragma endregion

#pragma region particle renderer parameters

Colorf ParticleRenderer::getSrcColor(float lifePercent)
{
	if (this->enableVariableColor) return colorOverLife(lifePercent);
	return Colorf::white;
}
Colorf ParticleRenderer::colorOverLife(float lifePercent)
{
	return Colorf::Lerp(this->beginColor, this->endColor, lifePercent);
}

float ParticleRenderer::getSrcVelocity(float lifePercent)
{
	if (this->enableVariableVelocity) return velocityOverLife(lifePercent);
	return static_cast<float>(Mathf::Randomf(4.0f, 8.0f))* this->velocity;
}
float ParticleRenderer::velocityOverLife(float lifePercent)
{
	float oneMinus = 1.0f - lifePercent;
	return this->beginVelocity * oneMinus + this->endVelocity * lifePercent;
}

float ParticleRenderer::getSrcSize(float lifePercent)
{
	if (this->enableVariableSize) return sizeOverLife(lifePercent);
	return this->size;
}
float ParticleRenderer::sizeOverLife(float lifePercent)
{
	float oneMinus = 1.0f - lifePercent;
	return this->beginSize * oneMinus + this->endSize * lifePercent;
}

float ParticleRenderer::getEmitInterval(float lifePercent) 
{
	if (this->enableVariableEmitSpeed) return this->lifeTime / this->maxNumber * this->beginSpeed;
	return this->lifeTime / this->maxNumber;
}

#pragma endregion

#pragma region renderer core

void ParticleRenderer::Init() 
{
	this->mesh = Primitive::GenPrimitive(Primitive::Type::Plane);
	mesh->Init([&](void) 
		{
			unsigned int vertexLocation = this->material->shader->getAttribLocation(VERTEX);
			glEnableVertexAttribArray(vertexLocation);
			glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
			unsigned int texcoordLocation = this->material->shader->getAttribLocation(TEXCOORD);
			glEnableVertexAttribArray(texcoordLocation);
			glVertexAttribPointer(texcoordLocation, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float) * 6));

			// ÑÕÉ«»º´æ
			glGenBuffers(1, &colorBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
			glBufferData(GL_ARRAY_BUFFER, this->maxNumber * sizeof(Colorf), NULL, GL_STATIC_DRAW);

			// ±ä»»»º´æ
			glGenBuffers(1, &transformBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, transformBuffer);
			glBufferData(GL_ARRAY_BUFFER, this->maxNumber * sizeof(Vector4), NULL, GL_DYNAMIC_DRAW);

			// Ðý×ª»º´æ
			glGenBuffers(1, &rotationBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, rotationBuffer);
			glBufferData(GL_ARRAY_BUFFER, this->maxNumber * sizeof(Vector4), NULL, GL_DYNAMIC_DRAW);

			glBindBuffer(GL_ARRAY_BUFFER, 0);
		});
	this->meshes.push_back(*mesh);}

void ParticleRenderer::Render() 
{
	if (nullptr == this->material)
	{
		PRINT_ERROR("ParticleRenderer's material can not be null.");
		return;
	}
	if (this->visible == false)
		return;

	if (this->usingParticles.size() <= 0)
		return;

	// this->material->AlphaTestFunc(GL_LESS, 0.0f);
	this->material->EnableAlphaTest();

	this->material->AlphaBlendFunc();
	this->material->EnableAlphaBlend();

	this->material->EnableDepthWrite(false);
	this->material->EnableDepthTest();
	this->material->EnableStencilTest();
	this->material->EnableCullFace();
	// this->material->renderMode = Material::Line;

	auto camera = Camera::current;
	glm::mat4 view = camera->GetViewMatrix();
	glm::mat4 projection;
	if (this->layer == Layer::UI) projection = camera->Get2DProjection();
	else projection = camera->GetProjectionMatrix();
	glm::mat4 model =
		glm::translate(glm::mat4(1.0), glm::vec3(this->transform->position.x, this->transform->position.y, this->transform->position.z)) *
		glm::rotate(glm::mat4(1.0f), glm::radians(this->transform->GetEulerangle().z), glm::vec3(0.0f, 0.0f, 1.0f)) *
		glm::rotate(glm::mat4(1.0f), glm::radians(this->transform->GetEulerangle().x), glm::vec3(1.0f, 0.0f, 0.0f)) *
		glm::rotate(glm::mat4(1.0f), glm::radians(this->transform->GetEulerangle().y), glm::vec3(0.0f, 1.0f, 0.0f)) *
		glm::scale(glm::mat4(1.0f), glm::vec3(this->transform->scale.x, this->transform->scale.y, this->transform->scale.z));

	glm::mat4 mvp = projection * view * model;
	this->material->shader->setMat4(MATRIX_MVP, mvp);
	glm::mat4 modelInverse = glm::inverse(model);
	this->material->shader->setMat4(World2Object, modelInverse);
	this->material->shader->setVec3(WorldSpaceCameraPos, Camera::main->transform->position);

	for (unsigned int i = 0; i < this->meshes.size(); i++) 
	{
		Mesh* mesh = &this->meshes[i];

		glBindVertexArray(mesh->VAO);
		// color buffer object
		glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
		glBufferSubData(GL_ARRAY_BUFFER, 0, this->existingNumber * sizeof(Colorf), &this->colors[0]);
		unsigned int colorLocation = this->material->shader->getAttribLocation(COLOR);
		glEnableVertexAttribArray(colorLocation);
		glVertexAttribPointer(colorLocation, 4, GL_FLOAT, GL_FALSE, sizeof(Colorf), (void*)0);
		glVertexAttribDivisor(colorLocation, 1);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// transform buffer object
		glBindBuffer(GL_ARRAY_BUFFER, transformBuffer);
		glBufferSubData(GL_ARRAY_BUFFER, 0, this->existingNumber * sizeof(Vector4), &this->transforms[0]);
		unsigned int transformLocation = this->material->shader->getAttribLocation("transform");
		glEnableVertexAttribArray(transformLocation);
		glVertexAttribPointer(transformLocation, 4, GL_FLOAT, GL_FALSE, sizeof(Vector4), (void*)0);
		glVertexAttribDivisor(transformLocation, 1);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// rotation buffer object
		glBindBuffer(GL_ARRAY_BUFFER, rotationBuffer);
		glBufferSubData(GL_ARRAY_BUFFER, 0, this->existingNumber * sizeof(Vector4), &this->rotations[0]);
		unsigned int rotationLocation = this->material->shader->getAttribLocation("rotation");
		glEnableVertexAttribArray(rotationLocation);
		glVertexAttribPointer(rotationLocation, 4, GL_FLOAT, GL_FALSE, sizeof(Vector4), (void*)0);
		glVertexAttribDivisor(rotationLocation, 1);
		glBindBuffer(GL_ARRAY_BUFFER,0);
		
		glBindVertexArray(0);
		this->material->shader->use();
		mesh->DrawInstanced(this->existingNumber);
		this->material->shader->disuse();
	}
}

#pragma endregion