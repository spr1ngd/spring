#include "instancedtechnology.h"
#include <vector>
#include "instancedrenderer.h"
#include "console.h"
#include "mathf.h"

using namespace std;
using namespace spring;

InstancedRenderer* instanceRenderer;
InstancedRenderer* instanceRendererNormal;

InstancedTechnology::InstancedTechnology() 
{

}

void InstancedTechnology::Awake() 
{
	if (!this->enabled)
		return;

	ModelLoader* loader = new ModelLoader();
	loader->Load("res/model/obj/cube.obj");
	Texture* texture = TextureLoader::Load("res/texture/grass.jpg", true);


	Material* instancedMaterial = new Material("res/shader/diffuse/diffuse(instance).vs","res/shader/diffuse/diffuse.fs");
	// Material* instancedMaterial = new Material("res/shader/diffuse/diffuse(instance).vs", "res/shader/geometry/normal.fs", "res/shader/geometry/normal.gs");
	instancedMaterial->CullFaceFunc(true, GL_BACK);
	instancedMaterial->renderMode = Material::RenderMode::Fill;
	instancedMaterial->enableGPUInstanced = true;
	instancedMaterial->shader->receiveShadow = false;
	instancedMaterial->castShadow = false;
	instancedMaterial->shader->setTexture(MAIN_TEX, texture->textureId);

	Material* instancedMaterialNormal = new Material("res/shader/diffuse/diffuse(instance)normal.vs", "res/shader/geometry/normal.fs", "res/shader/geometry/normal.gs");
	instancedMaterialNormal->CullFaceFunc(true, GL_BACK);
	instancedMaterialNormal->renderMode = Material::RenderMode::Fill;
	instancedMaterialNormal->enableGPUInstanced = true;
	instancedMaterialNormal->shader->receiveShadow = false;
	instancedMaterialNormal->castShadow = false;
	instancedMaterialNormal->shader->setTexture(MAIN_TEX, texture->textureId);

	instanceRenderer = new InstancedRenderer(instancedMaterial);
	instanceRenderer->mesh = loader->meshes[0];

	instanceRendererNormal = new InstancedRenderer(instancedMaterialNormal);
	instanceRendererNormal->mesh = loader->meshes[0];

	Mathf::RandomSeed();
	for (unsigned int i = 0; i < 1; i++)
	{
		auto randomX = (float)Mathf::Random(-5, 5);
		auto randomY = (float)Mathf::Random(-5, 5);
		auto randomZ = (float)Mathf::Random(-5, 5);
		Vector3 position = Vector3(randomX, randomY, randomZ);
		instanceRenderer->AddInstance(position, Vector3::zero, Vector3::one);
		instanceRendererNormal->AddInstance(position, Vector3::zero, Vector3::one);
	}
	instanceRenderer->Init();
	instanceRendererNormal->Init();
}

void InstancedTechnology::Update() 
{
	if (!this->enabled)
		return;

}

void InstancedTechnology::Destroy()
{
	if (!this->enabled)
		return;

}