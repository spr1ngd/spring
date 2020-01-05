#include "physically_based_rendering.h"
#include "springengine.h"
#include <vector>
#include <string>

using namespace spring;
using namespace spring::editor;
using namespace std;

vector<MeshRenderer*> spheres;

physically_based_rendering::physically_based_rendering() 
{
	this->enabled = false;
}

void physically_based_rendering::Awake() 
{
	if (!this->enabled)
		return; 

	ModelLoader* loader = new ModelLoader(); // todo : replaced model loader by resources manager
	loader->Load("res/model/obj/sphere.obj");

	const char* albedo = "albedo";
	const char* metal = "metal";
	const char* smoothness = "roughness";
	const char* ambient = "ao";

	Colorf albedoValue = Colorf(1.0f, 0.0f, 0.0f, 1.0f);
	Colorf ambientValue = Colorf::white;

	for (int x = 0; x < 10; x++) 
	{
		for (int y = 0; y < 10; y++) 
		{
			Vector3 pos =(Vector3((float)x, (float)y, 0.0f) + Vector3(-5.0f, -5.0f, 0.0f)) * 3.0f;

			Shader* pbs = Shader::Load("pbs/pbs.vs","pbs/pbs.fs");
			Shader* pbsWithIrradiance = Shader::Load("pbs/pbs.vs", "pbs/pbs(irradiance).fs");

			Material* pbsMat = new Material(pbsWithIrradiance);
			// Material* pbs = new Material("res/shader/diffuse/diffuse.vs", "res/shader/diffuse/diffuse.fs");
			pbsMat->shader->receiveShadow = false;

			float smoothnessValue = x * 0.1f;
			float metalValue = y * 0.1f;

			pbsMat->shader->setCubemap("irradianceMap", Skybox::irradianceCubemap);
			pbsMat->shader->setColor(albedo, albedoValue); // 反射率
			pbsMat->shader->setFloat(metal, metalValue); // 金属度
			pbsMat->shader->setFloat(smoothness,1.0f - smoothnessValue); //光滑度
			pbsMat->shader->setColor(ambient, ambientValue); // 环境光照

			MeshRenderer* meshRenderer = new MeshRenderer(pbsMat);
			meshRenderer->meshes = loader->meshes;
			meshRenderer->Init();
			meshRenderer->name = "pbs";
			meshRenderer->transform->SetPosition(pos);
			spheres.push_back(meshRenderer);
		}
	}
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