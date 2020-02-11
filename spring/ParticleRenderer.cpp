#include "particlerenderer.h"
#include "particle.h"
#include "primitive.h"

using namespace std;
using namespace spring;

std::vector<ParticleRenderer*> ParticleRenderer::particles;

ParticleRenderer::ParticleRenderer() 
{
	Shader* particle = Shader::Load("particle/particle.vs","particle/particle.fs");
	Material* particleMaterial = new Material(particle);
	this->material = particleMaterial;
	this->maxNumber = 20000;
	this->Init();
	particles.push_back(this);
}

ParticleRenderer::ParticleRenderer(Material* material) 
{
	this->material = material;
	this->Init();
	particles.push_back(this);
}

ParticleRenderer::~ParticleRenderer()
{
	// todo : destroy material & shader program instance
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
	// clear all particles status 
	// clear all particles properties
}

void ParticleRenderer::Update() 
{
	Mathf::RandomSeed();
	for (ParticleRenderer* particleRenderer : particles) 
	{
		if (!particleRenderer->playing)
			return;
		if (particleRenderer->existingNumber < particleRenderer->maxNumber)
		{
			Particle* particle = generate();
			particle = emit(particle);
			particleRenderer->usingParticles.push_back(particle);
			particleRenderer->colors.push_back(Colorf::white);
			particleRenderer->transforms.push_back(Vector4(particle->setting.position.x, particle->setting.position.y, particle->setting.position.z,particle->setting.size));
			particleRenderer->existingNumber++;
		}
		else
		{
			// calculate all particles life cycle , and playing particles physical motion
			for (unsigned int i = 0; i < particleRenderer->usingParticles.size(); i++) 
			{
				auto alivePartice = particleRenderer->usingParticles[i];
				emit(alivePartice);

				auto position = alivePartice->setting.position;
				alivePartice->setting.color = Colorf(Mathf::Abs(Mathf::Sin(alivePartice->setting.existingTime)));
				particleRenderer->colors[i] = alivePartice->setting.color;

				float y = position.y - Timer::deltaTime;
				if (y < -50.0f)
					y = 50.0f;
				alivePartice->setting.position = Vector3(position.x, y, position.z);
				particleRenderer->transforms[i] = Vector4(alivePartice->setting.position.x, alivePartice->setting.position.y, alivePartice->setting.position.z, alivePartice->setting.size);
			}

			// update color array 
			// update transform array
		}
	}
}

#pragma endregion

#pragma region particles emitter and generator

Particle* ParticleRenderer::emit(Particle* particle)
{
	// todo : generate random particle properties
	particle->setting.existingTime += Timer::deltaTime;
	return particle;
}

Particle* ParticleRenderer::generate()
{
	// todo : generate mesh data (contains vertex data / texcoord)
	Particle* particle = new Particle();
	particle->setting.lifeTime = 30.0f;
	particle->setting.existingTime = Mathf::Randomf(0.0f,particle->setting.lifeTime);
	return particle;
}

#pragma endregion

// #TODO refactor init and render methods . 
void ParticleRenderer::Init() 
{
	// 初始化第一个粒子
	Mathf::RandomSeed();
	for (unsigned int i = 0; i < this->maxNumber; i++)
	{
		Particle* particle = generate();
		particle = emit(particle);
		particle->setting.size = static_cast<float>(Mathf::Randomf(0.25f,3.0f));
		particle->setting.position = Vector3(Mathf::Randomf(-50.0f, 50.0f), Mathf::Randomf(-50.0f, 50.0f), Mathf::Randomf(-50.0f, 50.0f));
		this->usingParticles.push_back(particle);
		this->colors.push_back(Colorf::white);
		this->transforms.push_back(Vector4(particle->setting.position.x, particle->setting.position.y, particle->setting.position.z, particle->setting.size));
		this->existingNumber++;
	}

	this->mesh = Primitive::GenPrimitive(Primitive::Type::Plane);
	mesh->Init([&](void) 
		{
			unsigned int vertexLocation = this->material->shader->getLocation(VERTEX);
			glEnableVertexAttribArray(vertexLocation);
			glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
			unsigned int texcoordLocation = this->material->shader->getLocation(TEXCOORD);
			glEnableVertexAttribArray(texcoordLocation);
			glVertexAttribPointer(texcoordLocation, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float) * 6));

			// 颜色缓存
			glGenBuffers(1, &colorBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
			glBufferData(GL_ARRAY_BUFFER, 20000 * sizeof(Colorf), NULL, GL_STATIC_DRAW);
			glBufferSubData(GL_ARRAY_BUFFER, 0, 20000 * sizeof(Colorf), &this->colors[0]);
			unsigned int colorLocation = this->material->shader->getLocation(COLOR);
			glEnableVertexAttribArray(colorLocation);
			glVertexAttribPointer(colorLocation, 4, GL_FLOAT, GL_FALSE, sizeof(Colorf), (void*)0);
			glVertexAttribDivisor(colorLocation, 1);

			// 变换缓存
			glGenBuffers(1, &transformBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, transformBuffer);
			glBufferData(GL_ARRAY_BUFFER, 20000 * sizeof(Vector4), NULL, GL_STATIC_DRAW);
			glBufferSubData(GL_ARRAY_BUFFER, 0, 20000 * sizeof(Vector4), &this->transforms[0]);

			unsigned int transformLocation = this->material->shader->getAttribLocation("transform");
			glEnableVertexAttribArray(transformLocation);
			glVertexAttribPointer(transformLocation, 4, GL_FLOAT, GL_FALSE, sizeof(Vector4), (void*)0);
			glVertexAttribDivisor(transformLocation, 1);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		});
	this->meshes.push_back(*mesh);
	auto texture = TextureLoader::Load("res/texture/snow.png");
	this->material->shader->setTexture(MAIN_TEX,texture->textureId);
}

void ParticleRenderer::Render() 
{
	if (nullptr == this->material)
	{
		Console::ErrorFormat("ParticleRenderer's material can not be null.");
		return;
	}
	if (this->visible == false)
		return;

	this->material->EnableAlphaTest();
	this->material->AlphaBlendFunc(true);
	this->material->EnableAlphaBlend();
	this->material->EnableDepthWrite(false);
	this->material->EnableDepthTest();
	this->material->EnableStencilTest();
	// this->material->CullFaceFunc(true, GL_BACK);
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
		glBufferSubData(GL_ARRAY_BUFFER, 0, 20000 * sizeof(Colorf), &this->colors[0]);
		unsigned int colorLocation = this->material->shader->getLocation(COLOR);
		glEnableVertexAttribArray(colorLocation);
		glVertexAttribPointer(colorLocation, 4, GL_FLOAT, GL_FALSE, sizeof(Colorf), (void*)0);
		glVertexAttribDivisor(colorLocation, 1);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// transform buffer object
		glBindBuffer(GL_ARRAY_BUFFER, transformBuffer);
		glBufferSubData(GL_ARRAY_BUFFER, 0, 20000 * sizeof(Vector4), &this->transforms[0]);
		unsigned int transformLocation = this->material->shader->getAttribLocation("transform");
		glEnableVertexAttribArray(transformLocation);
		glVertexAttribPointer(transformLocation, 4, GL_FLOAT, GL_FALSE, sizeof(Vector4), (void*)0);
		glVertexAttribDivisor(transformLocation, 1);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		this->material->shader->use();
		mesh->DrawInstanced(this->existingNumber);
		this->material->shader->disuse();
	}
}