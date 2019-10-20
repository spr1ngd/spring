#pragma once
#include "springengine.h"

using namespace spring;

class Matrix4x4Sample : public Behaviour
{
private:
	bool enabled = true;
	MeshRenderer* sun;
	MeshRenderer* earth;
public:
	void Awake() override 
	{
		if (!enabled)
			return;
		ModelLoader loader = ModelLoader();
		loader.Load("res/model/obj/sphere.obj");

		Material sunMaterial("res/shader/diffuse/diffuse.vs", "res/shader/diffuse/diffuse.fs");
		sunMaterial.cullface = Material::CullFace::Back;
		sun = new MeshRenderer(sunMaterial);
		sun->meshes = loader.meshes;
		sun->textures = loader.loadedTextures;
		sun->Init();
		sun->transform->position = Vector3::zero;
		sun->transform->scale = Vector3(5.0f,5.0f,5.0f);
		TextureLoader textureLoader;
		auto sunTexture = textureLoader.Load("res/texture/sun.jpg");
		sun->material.shader->setTexture("MainTextureData.texture", sunTexture);
		sun->material.shader->setColor(MAIN_COLOR, Color(204, 204, 204, 128));
		sun->material.shader->setColor("Specular_Color", Color::white);
		sun->material.shader->setFloat("Specular_Intensity", 0.0f);
		sun->material.shader->setFloat("Specular_Attenuation", 64.0f);

		Material earthMaterial("res/shader/diffuse/diffuse.vs", "res/shader/diffuse/diffuse.fs");
		earthMaterial.cullface = Material::CullFace::Back;
		earth = new MeshRenderer(earthMaterial);
		earth->meshes = loader.meshes;
		earth->textures = loader.loadedTextures;
		earth->Init();
		earth->transform->scale = Vector3(0.5f);
		// earth->transform->position = Vector3(6.0f, 0.0f, 0.0f);
		auto earthTexture = textureLoader.Load("res/texture/earth.jpg");
		earth->material.shader->setTexture("MainTextureData.texture", earthTexture);
		earth->material.shader->setColor(MAIN_COLOR, Color(204, 204, 204, 128));
		earth->material.shader->setColor("Specular_Color", Color::white);
		earth->material.shader->setFloat("Specular_Intensity", 0.0f);
		earth->material.shader->setFloat("Specular_Attenuation", 64.0f);

		// todo fix : why axis helper
		Gizmos::DrawAxis(sun->transform,Vector3(6.0f));
		// Gizmos::DrawAxis(earth->transform); 

		sun->transform->SetEulerangle(Vector3(0.0f,0.0f,-15.0f));
		earth->transform->position = sun->transform->position + sun->transform->right * 15.0f;
		Gizmos::DrawCircle(sun->transform->position, sun->transform->up, 15.0f, 120);
	}

	float sunRotate = 0.0f;
	float earthRotate = 0.0f;
	float revolution = 0.0f;

	void Update() override
	{
		// 1. 太阳自转
		const Vector3 eulerangle = sun->transform->GetEulerangle();
		sunRotate += 0.5f;
		if (sunRotate > 360.0f)
			sunRotate -= 360.0f;
		Vector3 eulerY = Vector3(eulerangle.x, sunRotate, eulerangle.z);
		// todo : 太阳自转应该绕着自己的y轴进行旋转
		// sun->transform->SetEulerangle(eulerY);

		// 2. 地球自转
		const Vector3 ee = earth->transform->GetEulerangle();
		earthRotate += 1.5f;
		if (earthRotate > 360.0f)
			earthRotate -= 360.0f;
		Vector3 earthEuler = Vector3(ee.x,earthRotate,ee.z);
		earth->transform->SetEulerangle(earthEuler);

		// 3. 地球绕太阳转
		revolution += 5.0f;
		if (revolution > 360.0f)
			revolution -= 360.0f;
		earth->transform->RotateAround(sun->transform->position,sun->transform->up,1.0f); 
	}

	void Destroy() override 
	{

	}
};