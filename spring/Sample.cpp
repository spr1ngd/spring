#include "sample.h"
#include "matrix4x4sample.h"
#include "example.h"
#include "skybox.h"
#include "instancedtechnology.h"
#include "physically_based_rendering.h"
#include "physicsbasedrendering.h"
#include "springengine_scene.h"
#include "postprocessing.h"

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

	GameObject* mainCamera = new GameObject("Main Camera");
	camera = mainCamera->AddNode<Camera>();
	Camera::main = camera;
	camera->clearFlag = Camera::ClearFlag::Skybox;
	camera->background = Color(31, 113, 113, 255);
	camera->cullingMask->layers = Layer::Default | Layer::Skybox | Layer::PostProcessing;
	mainCamera->transform->SetPosition(Vector3(0.0f, 0.0f, 25.0f));
	mainCamera->transform->LookAt(Vector3::zero);

	orbit = mainCamera->AddNode<OrbitCamera>();
	orbit->target = Vector3(0.0f, 0.0f, 0.0f);// Vector3::zero;
	orbit->zoomSpeed = 1.0f;

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
		GameObject* skyboxGO = new GameObject("Skybox");
		skyboxGO->layer = Layer::Skybox;
		skybox = skyboxGO->AddNode<class::Skybox>();
		Material* skyboxMaterial = new Material(Shader::Load("skybox/6 Sided.vs", "skybox/6 Sided.fs"));
		skyboxMaterial->DepthTestFunc(false);
		skyboxMaterial->CullFaceFunc(false, GL_FRONT);
		auto cubemap = TextureLoader::LoadCubemap("res/texture/skybox/nature");
		skybox->material = skyboxMaterial;
		skybox->cubemap = cubemap;
		skybox->Initialize();
		// auto cubemap = TextureLoader::LoadCubemap("res/texture/skybox/night");

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
	}

	if (enableLights) 
	{
		GameObject* directionalLightGO = new GameObject("Directional Light");
		Light* light = directionalLightGO->AddNode<Light>();
		light->type = Light::Type::Directional;
		light->shadowType = Light::HardShadow;
		light->color = Color(255, 244, 214, 255);
		light->intensity = 10.0f;
		directionalLightGO->transform->SetPosition(Vector3(0.0f, 5.0f, 0.0f));
		directionalLightGO->transform->SetEulerangle(Vector3::down);

		GameObject* pointLightGO = new GameObject("Point Light");
		Light* pointLight1 = pointLightGO->AddNode<Light>();
		pointLight1->type = Light::Type::Directional;
		pointLight1->shadowType = Light::NoShadow;
		pointLight1->color = Color(255, 244, 214, 255);
		pointLight1->intensity = 3.0f;
		pointLightGO->transform->SetPosition(Vector3(10.0f, 10.0f, 10.0f));
		pointLightGO->transform->SetEulerangle(Vector3::left);
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

	// post processing
	GameObject* postProcessingGameObject = new GameObject("PostProcessing");
	postProcessingGameObject->layer = Layer::PostProcessing;
	PostProcessing::postprocessing = postProcessingGameObject->AddNode<class::PostProcessing>();
	PostProcessing::postprocessing->enabled = true;
	// pp->bloom 
	PostProcessing::postprocessing->bloom->enable = false;
	PostProcessing::postprocessing->Initialize();

	if (PostProcessing::postprocessing->enabled == false)
	{
		FrameBuffer* mainFramebuffer = new FrameBuffer(Screen::width, Screen::height);
		mainFramebuffer->antiAliasing = AntiAliasingLevel::Level2;
		mainFramebuffer->depthbuffer = FrameBuffer::OnlyDepth;
		mainFramebuffer->Initialize();
		Camera::main->framebuffer = mainFramebuffer;

		FrameBuffer* renderTarget = new FrameBuffer(Screen::width, Screen::height);
		renderTarget->Initialize();
		Camera::main->renderTarget = renderTarget;
	}
}

void Sample::Update() 
{
	timer += Timer::deltaTime;
	// skybox->material->shader->setFloat("time", timer);
	if (renderSkybox)
	{
		skybox->transform->position = Camera::main->transform->position;
	}
}

void Sample::Destroy() 
{

}