#include "sample.h"
#include "matrix4x4sample.h"
#include "example.h"
#include "skybox.h"
#include "instancedtechnology.h"
#include "physically_based_rendering.h"
#include "physicsbasedrendering.h"

using namespace spring;
using namespace spring::editor;

Matrix4x4Sample* matrix4x4Sample;
Example* example;
InstancedTechnology* instanced;
physically_based_rendering* pbr;

bool enabled = false;
bool renderSkybox = true;

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
	matrix4x4Sample = new Matrix4x4Sample();
	matrix4x4Sample->name = "Matrix4x4 Example";

	example = new Example();
	example->name = "Example";

	instanced = new InstancedTechnology();
	instanced->name = "Instancing Rendering Example";

	pbr = new physically_based_rendering();
	pbr->name = "Physically Based Rendering Example";

	instanced->enabled = false;
	pbr->enabled = true;
}

void Sample::Awake()
{
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

	if (renderSkybox) 
	{ 
		Material* skyboxMaterial = new Material("res/shader/skybox/6 Sided.vs", "res/shader/skybox/6 Sided.fs");
		auto cubemap = TextureLoader::LoadCubemap("res/texture/skybox/nature");
		// auto cubemap = TextureLoader::LoadCubemap("res/texture/skybox/night");
		skybox = new class::Skybox(skyboxMaterial, cubemap);
		skybox->name = "__SKYBOX__";
		skybox->Init();
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
	
	Light* light = createLight(Light::Type::Directional, Color(255, 244, 214, 255), 10.0f, Vector3(0.0f, 5.0f, 0.0f), Vector3::down); light->shadowType = Light::NoShadow;
	light->name = "Directional Light";
	Light* pointLigh1 = createLight(Light::Type::Directional, Color(255, 244, 214, 255), 3.0f, Vector3(10.0f, 10.0f, 10.0f), Vector3::left); pointLigh1->shadowType = Light::NoShadow;
	pointLigh1->name = "Point Light";
	/*Light* pointLigh2 = createLight(Light::Type::Directional, Color(255, 244, 214, 255), 1.8f, Vector3(-10.0f, -10.0f, 20.0f), Vector3::right); pointLigh2->shadowType = Light::NoShadow;
	Light* pointLigh3 = createLight(Light::Type::Directional, Color(255, 244, 214, 255), 1.2f, Vector3(-10.0f, 10.0f,20.0f), Vector3::back); pointLigh3->shadowType = Light::NoShadow;*/
	//Light* pointLigh4 = createLight(Light::Type::Point, Color::green, 0.6f, Vector3(0.0f, 0.0f, -5.0f), Vector3::forward);
	//Light* spotLight = createLight(Light::Type::Spot, Color::yellow, 1.3f, Vector3(0.0f, 6.0f, 0.0f), Vector3::bottom);

#pragma endregion

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
	orbit->target = Vector3(0.0f, 0.0f, 0.0f);// Vector3::zero;
	orbit->zoomSpeed = 1.0f;

	// world position coordinate
	// Gizmos::DrawAxis(Vector3::zero, Vector3(3.0f));

#pragma endregion

#pragma region draw triangle by encapsuled object 

	if (enabled) 
	{
		// draw light model
		ModelLoader loader = ModelLoader();
		loader.Load("res/model/obj/cube.obj");
		Material lightModelMat("res/shader/unlit/color.vs", "res/shader/unlit/color.fs");
		lightModel = new MeshRenderer(&lightModelMat);
		lightModel->meshes = loader.meshes;
		lightModel->textures = loader.loadedTextures;
		lightModel->Init();
		lightModel->transform->scale = Vector3(1.0f);
		lightModel->material->shader->setColor(MAIN_COLOR, Color::yellow);

		ModelLoader modelLoader = ModelLoader();
		modelLoader.Load("res/model/fbx/sphere.fbx");

		int sphereCount = 1;
		for (int i = 0; i < sphereCount; i++)
		{
			for (int j = 0; j < sphereCount; j++)
			{
				Material* mat = new Material("res/shader/diffuse/diffuse.vs", "res/shader/diffuse/transparency.fs");
				mat->name = "diffuse";
				mat->renderMode = Material::Fill;
				mats.push_back(mat);

				MeshRenderer* meshRenderer = new MeshRenderer(mat);
				meshRenderer->meshes = modelLoader.meshes;
				meshRenderer->textures = modelLoader.loadedTextures;
				meshRenderer->Init();
				meshRenderer->transform->position = Vector3(-10.0f + i * 2.0f, 0.0, -10.0f + j * 2.0f);
				meshRenderer->transform->scale = Vector3(1.0f);
				meshRenderer->transform->SetEulerangle(Vector3(-90.0f, 0.0f, 0.0f));
				meshRenderer->material->shader->setColor(MAIN_COLOR, Color(204, 204, 204, 128));
				meshRenderer->material->shader->setColor("Specular_Color", Color::white);
				meshRenderer->material->shader->setFloat("Specular_Intensity", 1.0f);
				meshRenderer->material->shader->setFloat("Specular_Attenuation", 64.0f);
				renderers.push_back(meshRenderer);
			}
		}

		Gizmos::DrawAxis(lightModel->transform);
	}

#pragma endregion
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
		float angleDelta = speed * Timer::deltaTime;
		/*lightModel->transform->eulerangle.z += angleDelta;
		if (lightModel->transform->eulerangle.z > 360.0f)
			lightModel->transform->eulerangle.z -= 360.0f;*/
	}
}

void Sample::Destroy() 
{
	if (enabled == false)
		return;
}