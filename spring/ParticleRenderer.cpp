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
	this->maxNumber = 100;
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
	for (auto particleRenderer : particles) 
	{
		/*if (!particleRenderer->playing)
			return;*/

		// if exist particle number less equal maxNumber -> generate new particle and add new particle to using particles array
		// else update particles and calculate particle life time 
		// -> if particle existing time greater than life time , recycle particle to unused paritcles array
		if (particleRenderer->existingNumber < particleRenderer->maxNumber)
		{
			Particle* particle = generate();
			particle = emit(particle);
			particleRenderer->usingParticles.push_back(particle);
			particleRenderer->colors.push_back(Colorf::white);
			particleRenderer->transforms.push_back(Vector4(particle->setting.position.x, particle->setting.position.y, particle->setting.position.z,particle->setting.size));
			particleRenderer->existingNumber++;
			Console::LogFormat("particle existing number %d , max number %d",particleRenderer->existingNumber,particleRenderer->maxNumber);
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
	}
}

#pragma endregion

#pragma region particles emitter and generator

Particle* ParticleRenderer::emit(Particle* particle)
{
	
	// todo : generate random particle properties
	// particle->setting
	return particle;
}

Particle* ParticleRenderer::generate()
{
	// todo : generate mesh data (contains vertex data / texcoord)
	Particle* particle = new Particle();
	return particle;
}

#pragma endregion



void ParticleRenderer::Init() 
{
	//// 初始化第一个粒子
	Mathf::RandomSeed();
	// FIXED : 生成的例子的状态不够随机，因为Mathf::Randomf函数有问题，在短时间内进行随机时，无法产生随机数
	for (unsigned int i = 0; i < this->maxNumber; i++)
	{
		Particle* particle = generate();
		particle = emit(particle);
		particle->setting.size = static_cast<float>(Mathf::Randomf(0.25f,2.0f));
		particle->setting.position = Vector3(Mathf::Randomf(-5.0f, 5.0f), Mathf::Randomf(-5.0f, 5.0f), Mathf::Randomf(-5.0f, 5.0f));
		this->usingParticles.push_back(particle);
		this->colors.push_back(/*Colorf(Mathf::Randomf(), Mathf::Randomf(), Mathf::Randomf(), Mathf::Randomf())*/Colorf::white);
		this->transforms.push_back(Vector4(particle->setting.position.x, particle->setting.position.y, particle->setting.position.z, particle->setting.size));
		this->existingNumber++;
	}

	this->mesh = new Mesh();

	// vertices
	vector<Vertex> vertices;
	vector<unsigned int> indices;

	Vertex lefttop;
	lefttop.vertex = Vector3(-.5f, .5f, 0.0f);
	lefttop.texcoord = Vector2(0.0f, 1.0f);
	vertices.push_back(lefttop);

	Vertex leftbottom;
	leftbottom.vertex = Vector3(-.5f, -.5f, 0.0f);
	leftbottom.texcoord = Vector2(0.0f, 0.0f);
	vertices.push_back(leftbottom);

	Vertex rightbottom;
	rightbottom.vertex = Vector3(.5f, -.5f, 0.0f);
	rightbottom.texcoord = Vector2(1.0f, 0.0f);
	vertices.push_back(rightbottom);

	Vertex righttop;
	righttop.vertex = Vector3(.5f, .5f, 0.0f);
	righttop.texcoord = Vector2(1.0f, 1.0f);
	vertices.push_back(righttop);

	indices = { 0,1,2,2,3,0 };

	mesh->vertices = vertices;
	mesh->indices = indices;

	// 顶点数据缓存
	glGenBuffers(1, &this->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * mesh->vertices.size(), &mesh->vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// 顶点数组对象
	glGenVertexArrays(1, &this->vao);
	glBindVertexArray(this->vao);

	glBindBuffer(GL_ARRAY_BUFFER,this->vbo);
	unsigned int vertexLocation = this->material->shader->getLocation(VERTEX);
	glEnableVertexAttribArray(vertexLocation);
	glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),(void*)0);

	unsigned int texcoordLocation = this->material->shader->getLocation(TEXCOORD);
	glEnableVertexAttribArray(texcoordLocation);
	glVertexAttribPointer(texcoordLocation, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float) * 6));

	// 颜色缓存
	unsigned int colorBuffer;
	glGenBuffers(1, &colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, 10000 * sizeof(Colorf), &this->colors[0], GL_STATIC_DRAW);
	//glBufferSubData(GL_ARRAY_BUFFER, 0, 1000 * sizeof(Colorf), &this->colors[0]);

	unsigned int colorLocation = this->material->shader->getLocation(COLOR);
	glEnableVertexAttribArray(colorLocation);
	glVertexAttribPointer(colorLocation, 4, GL_FLOAT, GL_FALSE, sizeof(Colorf), (void*)0);
	glVertexAttribDivisor(colorLocation, 1);

	// 变换缓存
	unsigned int transformBuffer;
	glGenBuffers(1, &transformBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, transformBuffer);
	glBufferData(GL_ARRAY_BUFFER, 10000 * sizeof(Vector4), &this->transforms[0] ,GL_STATIC_DRAW);
	//glBufferSubData(GL_ARRAY_BUFFER, 0, 1000 * sizeof(Vector4), &this->transforms[0]);

	unsigned int transformLocation = this->material->shader->getAttribLocation("transform");
	glEnableVertexAttribArray(transformLocation);
	glVertexAttribPointer(transformLocation, 4, GL_FLOAT, GL_FALSE, sizeof(Vector4), (void*)0);
	glVertexAttribDivisor(transformLocation, 1);

	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindVertexArray(0);

	// 缓存索引对象
	glGenBuffers(1, &this->ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,this->ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(unsigned int) * mesh->indices.size(), &mesh->indices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

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

	// this->material->shader->setMat4(MATRIX_M, model);
	// this->material->shader->setMat4(MATRIX_V, view);
	// this->material->shader->setMat4(MATRIX_P, projection);

	glm::mat4 mvp = projection * view * model;
	this->material->shader->setMat4(MATRIX_MVP, mvp);
	glm::mat4 modelInverse = glm::inverse(model);
	this->material->shader->setMat4(World2Object,modelInverse);
	this->material->shader->setVec3(WorldSpaceCameraPos,Camera::main->transform->position);

	this->material->shader->use();

	glBindVertexArray(this->vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ibo);
	glDrawElementsInstanced(GL_TRIANGLES, this->mesh->indices.size(), GL_UNSIGNED_INT, 0, this->existingNumber);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	this->material->shader->disuse();
}