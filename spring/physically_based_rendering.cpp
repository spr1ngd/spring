#include "physically_based_rendering.h"
#include "springengine.h"
#include <vector>
#include <string>
#include "particlerenderer.h"
#include "particle.h"

using namespace spring;
using namespace spring::editor;
using namespace std;

vector<MeshRenderer*> spheres;

physically_based_rendering::physically_based_rendering() 
{
	this->enabled = false;
}

void displaySpheres() 
{
	ModelLoader* loader = new ModelLoader(); // todo : replaced model loader by resources manager
	loader->Load("res/model/obj/sphere.obj");

	const char* albedo = "albedo";
	const char* metal = "metal";
	const char* smoothness = "roughness";
	const char* ambient = "ao";

	Colorf albedoValue = Colorf(.6f, .6f, .6f, 1.0f);
	Colorf ambientValue = Colorf::white;

	for (int x = 0; x < 10; x++)
	{
		for (int y = 0; y < 10; y++)
		{
			Vector3 pos = (Vector3((float)x, (float)y, 0.0f) + Vector3(-5.0f, -5.0f, 0.0f)) * 3.0f;
			Shader* pbs = Shader::Load("pbs/pbs.vs", "pbs/pbs.fs");
			Shader* pbsWithIrradiance = Shader::Load("pbs/pbs.vs", "pbs/pbs(irradiance).fs");
			Shader* ibl = Shader::Load("pbs/pbs.vs", "pbs/pbs(ibl).fs");

			Material* pbsMat = new Material(ibl);
			// Material* pbs = new Material("res/shader/diffuse/diffuse.vs", "res/shader/diffuse/diffuse.fs");
			pbsMat->shader->receiveShadow = false;

			float smoothnessValue = x * 0.1f;
			float metalValue = y * 0.1f;

			pbsMat->shader->setCubemap("irradianceMap", Skybox::irradianceCubemap);
			pbsMat->shader->setCubemap("prefilterMap", Skybox::prefilter);
			pbsMat->shader->setTexture("prebrdfMap", Skybox::prebrdf->textureId);

			pbsMat->shader->setColor(albedo, albedoValue); // 反射率
			pbsMat->shader->setFloat(metal, metalValue); // 金属度
			pbsMat->shader->setFloat(smoothness, 1.0f - smoothnessValue); //光滑度
			pbsMat->shader->setColor(ambient, ambientValue); // 环境光照

			MeshRenderer* meshRenderer = new MeshRenderer(pbsMat);
			meshRenderer->meshes = loader->meshes;
			meshRenderer->Init();
			meshRenderer->name = "pbs(ibl)";
			meshRenderer->transform->SetPosition(pos);
			spheres.push_back(meshRenderer);
		}
	}
}

void starFighter() 
{
	// Texture* metallicTex = TextureLoader::Load("res/model/fbx/star fighter/StarSparrow_MetallicSmoothness.png");
	// Texture* normalTex = TextureLoader::Load("res/model/fbx/star fighter/StarSparrow_Normal.png");
	// Texture* albedoTex = TextureLoader::Load("res/model/fbx/star fighter/StarSparrow_Red.png");
	// Texture* emissionTex = TextureLoader::Load("res/model/fbx/star fighter/StarSparrow_Emission.png");

	Texture* metallicTex = TextureLoader::Load("res/model/fbx/star fighter 02/StarSparrow_MetallicSmoothness.png");
	Texture* normalTex = TextureLoader::Load("res/model/fbx/star fighter 02/StarSparrow_Normal.png");
	Texture* albedoTex = TextureLoader::Load("res/model/fbx/star fighter 02/StarSparrow_Green.png");
	Texture* emissionTex = TextureLoader::Load("res/model/fbx/star fighter 02/StarSparrow_Emission.png");

	ModelLoader* loader = new ModelLoader();
	// loader->Load("res/model/fbx/star fighter/star fighter 01.fbx");
	loader->Load("res/model/fbx/star fighter 02/star fighter 02.fbx");
	Shader* shader = Shader::Load("pbs/pbs.vs", "pbs/pbs(ibl).fs");
	Material* material = new Material(shader);

	material->shader->setCubemap("irradianceMap", Skybox::irradianceCubemap);
	material->shader->setCubemap("prefilterMap", Skybox::prefilter);
	material->shader->setTexture("prebrdfMap", Skybox::prebrdf->textureId);

	material->shader->setTexture("metallicTex", metallicTex->textureId);
	material->shader->setTexture("normalTex", normalTex->textureId);
	material->shader->setTexture("albedoTex", albedoTex->textureId);
	material->shader->setTexture("emissionTex", emissionTex->textureId);

	Colorf albedoValue = Colorf::white;
	Colorf ambientValue = Colorf::white;
	const char* albedo = "albedo";
	const char* metal = "metal";
	const char* roughness = "roughness";
	const char* ambient = "ao";
	material->shader->setColor(albedo, albedoValue); // 反射率
	material->shader->setFloat(metal, 1.0f); // 金属度
	material->shader->setFloat(roughness, 0.1f); // 粗糙度
	material->shader->setColor(ambient, ambientValue); // 环境光照

	MeshRenderer* fighter = new MeshRenderer(material);
	fighter->meshes = loader->meshes;
	fighter->Init();
	fighter->name = "star fighter 01";
	fighter->transform->position = Vector3::zero;
	fighter->transform->scale = Vector3(0.06f);

	delete loader;
}

void generateParticle() 
{
	ParticleRenderer* particle = new ParticleRenderer();
	particle->name = "Particle System";
	auto texture = TextureLoader::Load("res/texture/snow.png");
	particle->material->shader->setTexture(MAIN_TEX,texture->textureId);
	particle->maxNumber = 50;
	particle->lifeTime = 2.0;
	particle->velocity = 10.0f;
	particle->rotateSpeed = 0.0f;
	particle->size = 10.0f;
	particle->material->shader->setColor(MAIN_COLOR, Color::white);

	particle->enableVariableColor = false;
	particle->beginColor = Color::yellow;
	particle->endColor = Color::red;

	particle->enableVariableVelocity = true;
	particle->beginVelocity = 50.0f;
	particle->endVelocity = 100.0f;

	// cube shape
	// particle->shapeModule->shapeType = ParticleShapeModule::ShapeType::Cube;
	// particle->shapeModule->cubeProperties.size = 50.0f;

	// sphere shape
	particle->shapeModule->shapeType = ParticleShapeModule::Sphere;
	particle->shapeModule->sphereProperties.radius = 20.0f;

	particle->transform->position = Vector3(0.0f,0.0f,0.0f);
	particle->transform->eulerangle = Vector3(0.0f, 0.0f, 180.0f);
	particle->playing = true;
}

void physically_based_rendering::Awake() 
{
	if (!this->enabled)
		return; 

	// displaySpheres();
	generateParticle();
	starFighter();
}

void physically_based_rendering::Update() 
{
	if (!this->enabled)
		return;
}

void physically_based_rendering::Destroy()
{
	if (!this->enabled)
		return;
}