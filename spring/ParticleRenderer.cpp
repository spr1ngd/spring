#include "particlerenderer.h"
#include "particle.h"

using namespace std;
using namespace spring;

std::vector<ParticleRenderer*> ParticleRenderer::particles;

ParticleRenderer::ParticleRenderer() 
{
	Shader* particle = Shader::Load("particle/particle.vs","particle/particle.fs");
	Material* particleMaterial = new Material(particle);
	this->material = particleMaterial;
	particles.push_back(this);
}

ParticleRenderer::ParticleRenderer(Material* material) 
{
	this->material = material;
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
	for (auto particleRenderer : particles) 
	{
		if (!particleRenderer->playing)
			return;

		// if exist particle number less equal maxNumber -> generate new particle and add new particle to using particles array
		// else update particles and calculate particle life time 
		// -> if particle existing time greater than life time , recycle particle to unused paritcles array
		if (particleRenderer->existingNumber < particleRenderer->maxNumber)
		{
			Particle* particle = generate();
			particle = emit(particle);
			particleRenderer->usingParticles.push_back(particle);
			particleRenderer->existingNumber++;
		}
		else
		{
			// calculate all particles life cycle , and playing particles physical motion
			for (unsigned int i = 0; i < particleRenderer->usingParticles.size(); i++) 
			{
				auto alivePartice = particleRenderer->usingParticles[i];
				emit(alivePartice);
			}
		}
		Console::LogFormat("particle existing number %d , max number %d",particleRenderer->existingNumber,particleRenderer->maxNumber);
	}
}

#pragma endregion

#pragma region particles emitter and generator

Particle* ParticleRenderer::emit(Particle* particle)
{
	Mathf::RandomSeed();
	// todo : generate random particle properties
	// particle->setting
	particle->setting.size = Vector3(static_cast<float>(Mathf::Random(1, 100)));
	particle->setting.position = Vector3(static_cast<float>(Mathf::Random(-50, 50)));
	return particle;
}

Particle* ParticleRenderer::generate()
{
	// todo : generate mesh data (contains vertex data / texcoord)
	Particle* particle = new Particle();
	Mesh* mesh = new Mesh();

	// vertices
	vector<Vertex> vertices;
	vector<unsigned int> indices;

	Vertex leftTop;
	leftTop.vertex = Vector3(-0.5f, 0.5f, 0.0f);
	leftTop.texcoord = Vector2(0.0f, 1.0f);
	vertices.push_back(leftTop);

	Vertex leftBottom;
	leftBottom.vertex = Vector3(-0.5f, -0.5f, 0.0f);
	leftBottom.texcoord = Vector2(0.0f, 0.0f);
	vertices.push_back(leftBottom);

	Vertex rightBottom;
	rightBottom.vertex = Vector3(0.5f, -0.5f, 0.0f);
	rightBottom.texcoord = Vector2(1.0f, 0.0f);
	vertices.push_back(rightBottom);

	Vertex rightTop;
	rightTop.vertex = Vector3(0.5f, 0.5f, 0.0f);
	rightTop.texcoord = Vector2(1.0f, 1.0f);
	vertices.push_back(rightTop);

	// indices
	indices = { 0,1,2,2,3,0 };

	mesh->vertices = vertices;
	mesh->indices = indices;
	particle->mesh = mesh;

	Shader* particleShader = Shader::Load("particle/particle.vs", "particle/particle.fs");
	Material* particleMaterial = new Material(particleShader);
	particle->material = particleMaterial;

	mesh->Init([&](void)
		{
			GLuint verexLocation = particle->material->shader->getLocation(VERTEX);
			glEnableVertexAttribArray(verexLocation);
			glVertexAttribPointer(verexLocation, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

			GLuint normalLocation = particle->material->shader->getLocation(NORMAL);
			glEnableVertexAttribArray(normalLocation);
			glVertexAttribPointer(normalLocation, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float) * 3));

			GLuint texcoordLocation = particle->material->shader->getLocation(TEXCOORD);
			glEnableVertexAttribArray(texcoordLocation);
			glVertexAttribPointer(texcoordLocation, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float) * 6));

			GLuint colorLocation = particle->material->shader->getLocation(COLOR);
			glEnableVertexAttribArray(colorLocation);
			glVertexAttribPointer(colorLocation, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float) * 8));
		});

	return particle;
}

#pragma endregion



void ParticleRenderer::Init() 
{

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

	// todo : enable gpu instance rendering
	// first version : 
	for (unsigned int i = 0; i < usingParticles.size(); i++)
	{
		Particle* particle = usingParticles[i];

		particle->material->EnableAlphaTest();
		particle->material->EnableAlphaBlend();
		particle->material->EnableCullFace();
		particle->material->EnableDepthTest();
		particle->material->EnableStencilTest();

		// TODO: set particle renderer setting parameter to material.shader object.
		glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(particle->setting.position.x,particle->setting.position.y,particle->setting.position.z)) * 
						  glm::rotate(glm::mat4(1.0f),glm::radians(particle->setting.eulerangle.z),glm::vec3(0.0f,0.0f,1.0f)) *
						  glm::rotate(glm::mat4(1.0f),glm::radians(particle->setting.eulerangle.x),glm::vec3(1.0f,0.0f,0.0f)) * 
						  glm::rotate(glm::mat4(1.0f),glm::radians(particle->setting.eulerangle.y),glm::vec3(0.0f,1.0f,0.0f)) *
						  glm::scale(glm::mat4(1.0f),glm::vec3(particle->setting.size.x,particle->setting.size.y,particle->setting.size.z));

		glm::mat4 projection = Camera::current->GetProjectionMatrix();
		particle->material->shader->setMat4(MATRIX_M, model);
		particle->material->shader->setMat4(MATRIX_P, projection);

		particle->material->shader->use();
		particle->mesh->Draw();
		particle->material->shader->disuse();
	}
}