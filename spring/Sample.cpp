#include "sample.h"
#include "matrix4x4sample.h"
#include "example.h"
#include "skybox.h"
#include "instancedtechnology.h"
#include "physically_based_rendering.h"
#include "physicsbasedrendering.h"
#include "springengine_scene.h"

using namespace spring;
using namespace spring::editor;

Matrix4x4Sample* matrix4x4Sample;
Example* example;
InstancedTechnology* instanced;
physically_based_rendering* pbr;
springengine_scene* esScene;

bool renderSkybox = true;
bool enableLights = true;

Camera* camera;
OrbitCamera* orbit;
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

	camera = new Camera();
	camera->name = "Main Camera";
	camera->clearFlag = Camera::ClearFlag::Skybox;
	camera->background = Color(31, 113, 113, 255);
	camera->transform->SetPosition(Vector3(0.0f, 0.0f, 25.0f));
	camera->transform->LookAt(Vector3::zero);
	camera->cullingMask->remove(Layer::UI);
	Camera::main = camera;

	orbit = new OrbitCamera();
	orbit->name = "OrbitCamera";
	// TODO : 支持查找另一个Node对象
	orbit->target = Vector3(0.0f, 0.0f, 0.0f);// Vector3::zero;
	orbit->zoomSpeed = 1.0f;

	// world position coordinate
	// Gizmos::DrawAxis(Vector3::zero, Vector3(3.0f));

#pragma endregion

	auto createLight = [&](Light::Type lightType, Color lightColor, float intensity, Vector3 position, Vector3 eulerangle)
	{
		Light* light = new Light();
		light->type = lightType;
		light->color = lightColor;
		light->intensity = intensity;
		light->transform->SetEulerangle(eulerangle);
		light->transform->SetPosition(position);
		return light;
	};

	//Color(255, 244, 214, 255)
#pragma region directional light 

	Environment::ambient.color = Color(75, 75, 75, 255);

	// TODO 70MB
	if (renderSkybox) 
	{ 
		// TODO : 50MB内存消耗？？？？？
		Material* skyboxMaterial = new Material(Shader::Load("skybox/6 Sided.vs", "skybox/6 Sided.fs"));
		auto cubemap = TextureLoader::LoadCubemap("res/texture/skybox/nature");
		// auto cubemap = TextureLoader::LoadCubemap("res/texture/skybox/night");
		skybox = new class::Skybox(skyboxMaterial, cubemap);
		skybox->name = "__SKYBOX__";
		skybox->Initialize();

		// TODO : 这部分预处理占用了20MB内存
		// refactor these code to environment class.
		Cubemap* irradianceCubemap = PhysicsBasedRendering::CubemapConvolution(cubemap);
		PhysicsBasedRendering::irradiance = irradianceCubemap;

		Cubemap* prefilter = PhysicsBasedRendering::PreFilter(cubemap);
		PhysicsBasedRendering::prefilter = prefilter;

		Texture* prebrdf = PhysicsBasedRendering::PreBRDF(cubemap);
		PhysicsBasedRendering::prebrdf = prebrdf;

		skybox->SetCubemap(prefilter);
		Skybox::irradianceCubemap = irradianceCubemap;
		Skybox::prefilter = prefilter;
		Skybox::prebrdf = prebrdf;
		skybox->visible = true;
	}

	if (enableLights) 
	{
		Light* light = createLight(Light::Type::Directional, Color(255, 244, 214, 255), 10.0f, Vector3(0.0f, 5.0f, 0.0f), Vector3::down); 
		light->shadowType = Light::NoShadow;
		light->name = "Directional Light";

		Light* pointLigh1 = createLight(Light::Type::Directional, Color(255, 244, 214, 255), 3.0f, Vector3(10.0f, 10.0f, 10.0f), Vector3::left); 
		pointLigh1->shadowType = Light::NoShadow;
		pointLigh1->name = "Point Light";
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
		skybox->transform->position = Camera::main->transform->position;
	}
	if (visible) 
	{
		// float angleDelta = speed * Timer::deltaTime;
		/*lightModel->transform->eulerangle.z += angleDelta;
		if (lightModel->transform->eulerangle.z > 360.0f)
			lightModel->transform->eulerangle.z -= 360.0f;*/
	}
}

void Sample::Destroy() 
{

}