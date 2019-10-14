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
		earth->transform->position = Vector3(10.0f, 0.0f, 0.0f);
		auto earthTexture = textureLoader.Load("res/texture/earth.jpg");
		earth->material.shader->setTexture("MainTextureData.texture", earthTexture);
		earth->material.shader->setColor(MAIN_COLOR, Color(204, 204, 204, 128));
		earth->material.shader->setColor("Specular_Color", Color::white);
		earth->material.shader->setFloat("Specular_Intensity", 0.0f);
		earth->material.shader->setFloat("Specular_Attenuation", 64.0f);
	}
	void Update() override 
	{

	}
	void Destroy() override 
	{

	}
};