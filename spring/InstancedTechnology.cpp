#include "instancedtechnology.h"
#include <vector>
#include "instancedrenderer.h"
#include "console.h"
#include "mathf.h"

using namespace std;
using namespace spring;

InstancedRenderer* instanceRenderer;

InstancedTechnology::InstancedTechnology() 
{

}

void InstancedTechnology::Awake() 
{
	if (!this->enabled)
		return;

	ModelLoader* loader = new ModelLoader();
	loader->Load("res/model/obj/cube.obj");

	Material* instancedMaterial = new Material("res/shader/diffuse/diffuse(instance).vs","res/shader/diffuse/diffuse.fs");
	instancedMaterial->CullFaceFunc(true, GL_BACK);
	instancedMaterial->enableGPUInstanced = true;
	instancedMaterial->shader->receiveShadow = false;

	instanceRenderer = new InstancedRenderer(instancedMaterial);
	instanceRenderer->mesh = loader->meshes[0];
	instanceRenderer->Init();
	Mathf::RandomSeed();

	/*int maxVertUniformsVect;
	glGetIntegerv(GL_MAX_VERTEX_UNIFORM_VECTORS, &maxVertUniformsVect);
	Console::LogFormat("%d", maxVertUniformsVect);*/

	for (unsigned int i = 0; i < 300; i++) 
	{
		instanceRenderer->AddInstance(Vector3::zero,Vector3::zero,Vector3::one);
		auto randomX = (float)Mathf::Random(-20, 20);
		auto randomY = (float)Mathf::Random(-20, 20);
		auto randomZ = (float)Mathf::Random(-20, 20);
		Vector3 offset = Vector3(randomX, randomY, randomZ);
		char buffer[16];
		sprintf_s(buffer, "offsets[%d]", i);
		instancedMaterial->shader->setVec3(buffer, offset);
	}
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