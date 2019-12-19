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
	Texture* texture = TextureLoader::Load("res/model/fbx/747/747-400 texture.png");

	Material* instancedMaterial = new Material("res/shader/diffuse/diffuse(instance).vs","res/shader/diffuse/diffuse.fs");
	// Material* instancedMaterial = new Material("res/shader/diffuse/diffuse(instance).vs", "res/shader/geometry/normal.fs", "res/shader/geometry/normal.gs");
	instancedMaterial->CullFaceFunc(true, GL_BACK);
	instancedMaterial->renderMode = Material::RenderMode::Fill;
	instancedMaterial->enableGPUInstanced = true;
	instancedMaterial->shader->receiveShadow = false;
	instancedMaterial->castShadow = true;
	instancedMaterial->shader->setTexture(MAIN_TEX, texture->textureId);
	instancedMaterial->shader->setColor(MAIN_COLOR, Color(204, 204, 204, 128));
	instancedMaterial->shader->setColor("Specular_Color", Color::white);
	instancedMaterial->shader->setFloat("Specular_Intensity", 0.0f);
	instancedMaterial->shader->setFloat("Specular_Attenuation", 64.0f);

	Material* instancedMaterialNormal = new Material("res/shader/diffuse/diffuse(instance)normal.vs", "res/shader/geometry/normal.fs", "res/shader/geometry/normal.gs");
	instancedMaterialNormal->CullFaceFunc(true, GL_BACK);
	instancedMaterialNormal->renderMode = Material::RenderMode::Fill;
	instancedMaterialNormal->enableGPUInstanced = true;
	instancedMaterialNormal->shader->receiveShadow = false;
	instancedMaterialNormal->castShadow = true;
	instancedMaterialNormal->shader->setTexture(MAIN_TEX, texture->textureId);

	instanceRenderer = new InstancedRenderer(instancedMaterial);
	instanceRenderer->mesh = loader->meshes[0];

	// instanceRendererNormal = new InstancedRenderer(instancedMaterialNormal);
	// instanceRendererNormal->mesh = loader->meshes[0];

	Mathf::RandomSeed();
	for (unsigned int i = 0; i < 10000; i++)
	{
		auto randomX = (float)Mathf::Random(-100, 100);
		auto randomY = (float)Mathf::Random(-100, 100);
		auto randomZ = (float)Mathf::Random(-100, 100);
		Vector3 position = Vector3(randomX, randomY, randomZ);

		randomX = (float)Mathf::Randomf() * 2.0f;
		randomY = (float)Mathf::Randomf() * 2.0f;
		randomZ = (float)Mathf::Randomf() * 2.0f;
		Vector3 scale = Vector3(randomX, randomY, randomZ);

		instanceRenderer->AddInstance(position, Vector3::zero, scale);
		// instanceRendererNormal->AddInstance(position, Vector3::zero, Vector3::one);
	}
	instanceRenderer->Init();
	// instanceRendererNormal->Init();
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