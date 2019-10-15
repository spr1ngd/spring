#include "sample.h"
#include "matrix4x4sample.h"

using namespace spring;
using namespace spring::editor;

Matrix4x4Sample* matrix4x4Sample;

bool enabled = false;
Camera* camera;
OrbitCamera* orbit;
Skybox* skybox; 
MeshRenderer* lightModel;
vector<Material*> mats;
vector<MeshRenderer*> renderers;

float timer = 0.0f;
float speed = 5.0f;

Sample::Sample() 
{
	matrix4x4Sample = new Matrix4x4Sample();
}

void Sample::Awake()
{
	auto createLight = [&](Light::Type lightType, Color lightColor, float intensity, Vector3 position, Vector3 eulerangle)
	{
		Light* light = new Light();
		light->type = lightType;
		light->color = lightColor;
		light->intensity = intensity;
		light->transform->eulerangle = eulerangle;
		light->transform->position = position;
		return light;
	};

	//Color(255, 244, 214, 255)
#pragma region directional light 

	Environment::ambient.color = Color(75, 75, 75, 255);
	 
	Material skyboxMaterial("res/shader/skybox/6 Sided.vs", "res/shader/skybox/6 Sided.fs");
	skybox = new Skybox("6 Sided", skyboxMaterial);
	skybox->Init();

	Light* light = createLight(Light::Type::Directional, Color(255, 244, 214, 255), 0.7f, Vector3(10.0f, 10.0f, 10.0f), Vector3::down);
	//Light* pointLigh1 = createLight(Light::Type::Point, Color::red, 0.6f, Vector3(5.0f, 0.0f, 0.0f), Vector3::left);
	//Light* pointLigh2 = createLight(Light::Type::Point, Color::green, 0.6f, Vector3(-5.0f, 0.0f, 0.0f), Vector3::right);
	//Light* pointLigh3 = createLight(Light::Type::Point, Color::blue, 0.6f, Vector3(0.0f, 0.0f, 5.0f), Vector3::back);
	//Light* pointLigh4 = createLight(Light::Type::Point, Color::green, 0.6f, Vector3(0.0f, 0.0f, -5.0f), Vector3::forward);
	//Light* spotLight = createLight(Light::Type::Spot, Color::yellow, 1.3f, Vector3(0.0f, 6.0f, 0.0f), Vector3::bottom);

#pragma endregion

#pragma region scene camera setting

	camera = new Camera();
	camera->clearFlag = Camera::ClearFlag::Skybox;
	camera->background = Color(31, 113, 113, 255);
	camera->transform->position = Vector3(16.0f, 16.0f, 16.0f);
	camera->transform->LookAt(Vector3::zero);

	orbit = new OrbitCamera();
	orbit->target = Vector3::zero;
	orbit->zoomSpeed = 0.25f;

#pragma endregion

#pragma region draw triangle by encapsuled object 

	if (enabled) 
	{
		// draw light model
		ModelLoader loader = ModelLoader();
		loader.Load("res/model/obj/cube.obj");
		Material lightModelMat("res/shader/unlit/color.vs", "res/shader/unlit/color.fs");
		lightModel = new MeshRenderer(lightModelMat);
		lightModel->meshes = loader.meshes;
		lightModel->textures = loader.loadedTextures;
		lightModel->Init();
		lightModel->transform->scale = Vector3(1.0f);
		lightModel->material.shader->setColor(MAIN_COLOR, Color::yellow);

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

				MeshRenderer* meshRenderer = new MeshRenderer(*mat);
				meshRenderer->meshes = modelLoader.meshes;
				meshRenderer->textures = modelLoader.loadedTextures;
				meshRenderer->material.cullface = Material::CullFace::Back;
				meshRenderer->Init();
				meshRenderer->transform->position = Vector3(-10.0f + i * 2.0f, 0.0, -10.0f + j * 2.0f);
				meshRenderer->transform->scale = Vector3(1.0f);
				meshRenderer->transform->eulerangle = Vector3(-90.0f, 0.0f, 0.0f);
				meshRenderer->material.shader->setColor(MAIN_COLOR, Color(204, 204, 204, 128));
				meshRenderer->material.shader->setColor("Specular_Color", Color::white);
				meshRenderer->material.shader->setFloat("Specular_Intensity", 1.0f);
				meshRenderer->material.shader->setFloat("Specular_Attenuation", 64.0f);
				renderers.push_back(meshRenderer);
			}
		}

		Gizmos::DrawAxis(lightModel->transform);
	}

#pragma endregion
}

void Sample::Update() 
{
	camera->Render();
	timer += Timer::deltaTime;
	skybox->transform->position = Camera::main->transform->position;

	if (enable) 
	{
		float angleDelta = speed * Timer::deltaTime;
		lightModel->transform->eulerangle.z += angleDelta;
		if (lightModel->transform->eulerangle.z > 360.0f)
			lightModel->transform->eulerangle.z -= 360.0f;
	}
}

void Sample::Destroy() 
{
	if (enabled == false)
		return;
}