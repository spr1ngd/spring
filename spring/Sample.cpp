#include "sample.h"
#include "matrix4x4sample.h"
#include "example.h"
#include "skybox.h"
#include "instancedtechnology.h"
#include "physically_based_rendering.h"
#include "physicsbasedrendering.h"
#include "springengine_scene.h"
#include "postprocessing.h"
#include "firstplayercamera.h"
#include "thirdplayercamera.h"

using namespace spring;
using namespace spring::editor;

Matrix4x4Sample* matrix4x4Sample;
Example* example;
InstancedTechnology* instanced;
physically_based_rendering* pbr;
springengine_scene* esScene;

bool renderSkybox = true;
bool enableLights = true;

class::spring::Skybox* skybox; 
MeshRenderer* lightModel;
vector<Material*> mats;
vector<MeshRenderer*> renderers;

float timer = 0.0f;
float speed = 5.0f;

Sample::Sample() 
{

}

void Sample::Awake()
{
	esScene = new springengine_scene();
	esScene->name = "scene loader";

#pragma region scene camera setting



#pragma endregion

#pragma region directional light 

	Environment::SetAmbientSetting(Color(75, 75, 75, 255));
	Environment::SetShodowSetting(Environment::ShadowSetting::Octuple);

	// TODO 70MB
	if (renderSkybox) 
	{ 
		// TODO : 50MB内存消耗？？？？？
		GameObject* skyboxGO = new GameObject("Skybox");
		skyboxGO->SetFlag(HideFlags::HideFlags_HideInHierarchyWindow);
		skyboxGO->layer = Layer::Skybox;
		skybox = skyboxGO->AddNode<class::Skybox>();
		Material* skyboxMaterial = new Material(Shader::Load("skybox/6 Sided.vs", "skybox/6 Sided.fs"));
		skyboxMaterial->DepthTestFunc(false);
		skyboxMaterial->CullFaceFunc(false, GL_FRONT);
		auto cubemap = TextureLoader::LoadCubemap("res/texture/skybox/anotherplanet");
		// auto cubemap = TextureLoader::LoadCubemap("res/texture/skybox/nature");
		skybox->material = skyboxMaterial;
		skybox->cubemap = cubemap;
		skybox->Initialize();
		// auto cubemap = TextureLoader::LoadCubemap("res/texture/skybox/night");

		// TODO : 这部分预处理占用了20MB内存
		// refactor these code to environment class.
		PhysicsBasedRendering::CubemapConvolution(cubemap);
		PhysicsBasedRendering::PreFilter(cubemap);
		PhysicsBasedRendering::PreBRDF(cubemap);

		skybox->SetCubemap(cubemap);
		// skybox->SetCubemap(PhysicsBasedRendering::prefilter);
		Skybox::irradianceCubemap = PhysicsBasedRendering::irradiance;
		Skybox::prefilter = PhysicsBasedRendering::prefilter;
		Skybox::prebrdf = PhysicsBasedRendering::prebrdf;
	}

	if (enableLights) 
	{
		GameObject* directionalLightGO = new GameObject("Directional Light");
		Light* light = directionalLightGO->AddNode<Light>();
		light->type = Light::Type::Directional;
		light->shadowType = Light::HardShadow;
		light->layers.set(Layer::Default);
		light->color = Color(255, 244, 214, 255);
		light->setting.intensity = 10.0f;
		light->SetShadowMappingParams(1024, 150.0f, -1.0f, 300.0f);
		directionalLightGO->transform->SetPosition(Vector3(18.0f, 36.0f, 32.0f));
		directionalLightGO->transform->SetEulerangle(Vector3::down);

		// GameObject* pointLightGO = new GameObject("Point Light");
		// Light* pointLight1 = pointLightGO->AddNode<Light>();
		// pointLight1->type = Light::Type::Directional;
		// pointLight1->shadowType = Light::NoShadow;
		// pointLight1->color = Color(255, 244, 214, 255);
		// pointLight1->intensity = 3.0f;
		// pointLightGO->transform->SetPosition(Vector3(10.0f, 10.0f, 10.0f));
		// pointLightGO->transform->SetEulerangle(Vector3::left);
	}	

#pragma endregion

	// matrix4x4Sample = new Matrix4x4Sample();
	// matrix4x4Sample->name = "Matrix4x4 Example";
	// 
	// example = new Example();
	// example->name = "Example";

	// instanced = new InstancedTechnology();
	// instanced->name = "Instancing Rendering Example";

	pbr = new physically_based_rendering();
	pbr->name = "Physically Based Rendering Example";
	pbr->enabled = true;
}

void Sample::Update() 
{
	timer += Timer::deltaTime;
	// skybox->material->shader->setFloat("time", timer);
	if (renderSkybox)
	{
		skybox->transform->SetPosition(Camera::main->transform->position);
	}
}

void Sample::Destroy() 
{

}