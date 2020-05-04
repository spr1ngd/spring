#include "physically_based_rendering.h"
#include "springengine.h"
#include <vector>
#include <string>
#include "particlerenderer.h"
#include "particle.h"
#include "picking.h"
#include "console.h"

using namespace spring;
using namespace spring::editor;
using namespace std;

vector<MeshRenderer*> spheres;
// ParticleRenderer* particle;
// ParticleRenderer* particle2;

GameObject* fighterGO;
GameObject* particleGO;
GameObject* particle2GO;
GameObject* mobiusband;

physically_based_rendering::physically_based_rendering() 
{

}

void displaySpheres() 
{
	Mesh& mesh = ModelLoader::Load("obj/sphere.obj");

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
			meshRenderer->mesh = &mesh;
			meshRenderer->Initialize();
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
	fighterGO = new GameObject("star fighter");
	auto fighter = fighterGO->AddNode<MeshRenderer>();

	Texture* metallicTex = TextureLoader::Load("res/model/fbx/star fighter 02/StarSparrow_MetallicSmoothness.png");
	Texture* normalTex = TextureLoader::Load("res/model/fbx/star fighter 02/StarSparrow_Normal.png");
	Texture* albedoTex = TextureLoader::Load("res/model/fbx/star fighter 02/StarSparrow_Green.png");
	Texture* emissionTex = TextureLoader::Load("res/model/fbx/star fighter 02/StarSparrow_Emission.png");

	// // loader->Load("res/model/fbx/star fighter/star fighter 01.fbx");
	Mesh& mesh = ModelLoader::Load("fbx/star fighter 02/star fighter 02.fbx");
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
	Colorf emissionValue = Colorf::white;
	const char* albedo = "albedo";
	const char* metal = "metal";
	const char* roughness = "roughness";
	const char* ambient = "ao";
	const char* emission = "emissionColor";
	material->shader->setColor(albedo, albedoValue); // 反射率
	material->shader->setFloat(metal, 1.0f); // 金属度
	material->shader->setFloat(roughness, 0.1f); // 粗糙度
	material->shader->setColor(ambient, ambientValue); // 环境光照
	material->shader->setColor(emission,emissionValue);// 自发光

	fighter->material = material;
	fighter->mesh = &mesh;
	// fighter->Initialize();
	fighter->transform->position = Vector3::zero;
	fighter->transform->scale = Vector3(0.06f);
}

void generateMobiusBand() 
{
	mobiusband = new GameObject("Mobiusband");//mobiusband.fbx
	MeshRenderer* mobiusRenderer = mobiusband->AddNode<MeshRenderer>();
	mobiusRenderer->mesh = &ModelLoader::Load("fbx/mobiusband.fbx");
	// mobiusRenderer->mesh = &ModelLoader::Load("obj/cube.obj");
	mobiusRenderer->material = new Material(Shader::Load("pbs/pbs.vs", "pbs/pbs(ibl).fs"));
	mobiusRenderer->material->shader->setCubemap("irradianceMap", Skybox::irradianceCubemap);
	mobiusRenderer->material->shader->setCubemap("prefilterMap", Skybox::prefilter);
	mobiusRenderer->material->shader->setTexture("prebrdfMap", Skybox::prebrdf->textureId);
	Colorf albedoValue = Colorf::white;
	Colorf ambientValue = Colorf::white;
	Colorf emissionValue = Colorf::white;
	const char* albedo = "albedo";
	const char* metal = "metal";
	const char* roughness = "roughness";
	const char* ambient = "ao";
	const char* emission = "emissionColor";
	Texture* albedoTex = TextureLoader::Load("res/model/fbx/star fighter 02/StarSparrow_Green.png");
	mobiusRenderer->material->shader->setTexture("albedoTex", albedoTex->textureId);
	mobiusRenderer->material->shader->setColor(albedo, albedoValue); // 反射率
	mobiusRenderer->material->shader->setFloat(metal, 1.0f); // 金属度
	mobiusRenderer->material->shader->setFloat(roughness, 0.1f); // 粗糙度
	mobiusRenderer->material->shader->setColor(ambient, ambientValue); // 环境光照
	mobiusRenderer->material->shader->setColor(emission, emissionValue);// 自发光
	mobiusband->transform->scale = Vector3(10.0f);
	mobiusband->transform->position = Vector3::zero;
}

void generateParticle() 
{
	particleGO = new GameObject("particle system left");
	// auto particle = new ParticleRenderer();
	auto particle = particleGO->AddNode<ParticleRenderer>();
	particle->name = "Particle System Left";
	auto texture = TextureLoader::Load("res/texture/photon.png");
	particle->material->shader->setTexture(MAIN_TEX, texture->textureId);
	particle->maxNumber = 5000;
	particle->lifeTime = .2f;
	particle->velocity = 10.0f;
	particle->rotateSpeed = 0.0f;
	particle->size = 8.0f;
	particle->material->shader->setColor(MAIN_COLOR, Colorf(1.5f, 1.5f, 1.5f, 1.0f));

	particle->enableVariableColor = true;
	particle->beginColor = Color::yellow;
	particle->endColor = Color::cyan;

	particle->enableVariableVelocity = false;
	particle->beginVelocity = 50.0f;
	particle->endVelocity = 100.0f;

	particle->enableVariableEmitSpeed = true;
	particle->beginSpeed = 10.0f;
	particle->endSpeed = 10.0f;

	particle->enableVariableSize = true;
	particle->beginSize = 5.0f;
	particle->endSize = 1.0f;

	// cube shape
	// particle->shapeModule->shapeType = ParticleShapeModule::ShapeType::Cube;
	// particle->shapeModule->cubeProperties.size = 50.0f;

	// sphere shape
	// particle->shapeModule->shapeType = ParticleShapeModule::ShapeType::Sphere;
	// particle->shapeModule->sphereProperties.radius = 20.0f;

	// hemisphere shape
	// particle->shapeModule->shapeType = ParticleShapeModule::ShapeType::Hemishpere;
	// particle->shapeModule->hemisphereProperties.radius = 10.0f;
	// particle->shapeModule->hemisphereProperties.eulerangle = Vector3(90.0f,0.0f,0.0f);

	// cone shape
	particle->shapeModule->shapeType = ParticleShapeModule::ShapeType::Cone;
	particle->shapeModule->coneProperties.bottomRadius = 1.8f;
	particle->shapeModule->coneProperties.topRadius = 0.0;
	particle->shapeModule->coneProperties.height = 15.0f;

	// rectangle shape
	// particle->shapeModule->shapeType = ParticleShapeModule::ShapeType::Rectangle;
	// particle->shapeModule->rectangleProperties.width = 2.0f;
	// particle->shapeModule->rectangleProperties.length = 80.0f;

	particle->transform->position = Vector3(22.0f, 1.5f, -19.0f);
	particle->transform->eulerangle = Vector3(-90.0f, 0.0f, 0.0f);
	particle->playing = true;
}

void generateParticle2()
{
	particle2GO = new GameObject("particle system right");
	// auto particle2 = new ParticleRenderer();
	auto particle2 = particle2GO->AddNode<ParticleRenderer>();
	particle2->name = "Particle System Right";
	auto texture = TextureLoader::Load("res/texture/photon.png");
	particle2->material->shader->setTexture(MAIN_TEX, texture->textureId);
	particle2->maxNumber = 5000;
	particle2->lifeTime = .2f;
	particle2->velocity = 10.0f;
	particle2->rotateSpeed = 0.0f;
	particle2->size = 8.0f;
	particle2->material->shader->setColor(MAIN_COLOR, Colorf(1.5f, 1.5f, 1.5f, 1.0f));

	particle2->enableVariableColor = true;
	particle2->beginColor = Color::yellow;
	particle2->endColor = Color::cyan;

	particle2->enableVariableVelocity = false;
	particle2->beginVelocity = 50.0f;
	particle2->endVelocity = 100.0f;

	particle2->enableVariableEmitSpeed = true;
	particle2->beginSpeed = 10.0f;
	particle2->endSpeed = 10.0f;

	particle2->enableVariableSize = true;
	particle2->beginSize = 5.0f;
	particle2->endSize = 1.0f;

	// cube shape
	// particle->shapeModule->shapeType = ParticleShapeModule::ShapeType::Cube;
	// particle->shapeModule->cubeProperties.size = 50.0f;

	// sphere shape
	// particle->shapeModule->shapeType = ParticleShapeModule::ShapeType::Sphere;
	// particle->shapeModule->sphereProperties.radius = 20.0f;

	// hemisphere shape
	// particle->shapeModule->shapeType = ParticleShapeModule::ShapeType::Hemishpere;
	// particle->shapeModule->hemisphereProperties.radius = 10.0f;
	// particle->shapeModule->hemisphereProperties.eulerangle = Vector3(90.0f,0.0f,0.0f);

	// cone shape
	particle2->shapeModule->shapeType = ParticleShapeModule::ShapeType::Cone;
	particle2->shapeModule->coneProperties.bottomRadius = 1.8f;
	particle2->shapeModule->coneProperties.topRadius = 0.0;
	particle2->shapeModule->coneProperties.height = 15.0f;

	// rectangle shape
	// particle->shapeModule->shapeType = ParticleShapeModule::ShapeType::Rectangle;
	// particle->shapeModule->rectangleProperties.width = 2.0f;
	// particle->shapeModule->rectangleProperties.length = 80.0f;

	particle2->transform->position = Vector3(-22.0f, 1.5f, -19.0f);
	particle2->transform->eulerangle = Vector3(-90.0f, 0.0f, 0.0f);
	particle2->playing = true;
}

void physically_based_rendering::Awake() 
{
	// generateMobiusBand();
	// starFighter();
	// generateParticle();
	// generateParticle2();
	// particleGO->SetParent(fighterGO);
	// particle2GO->SetParent(fighterGO);
}

void physically_based_rendering::Update() 
{ 
	if (nullptr != mobiusband)
	{
		mobiusband->transform->eulerangle += Vector3(0.0f,0.5f,0.0f);
	}
}

void physically_based_rendering::Destroy()
{ 
}