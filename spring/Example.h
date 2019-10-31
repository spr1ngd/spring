#pragma once
#include "springengine.h"
#include "gui.h"
#include "rect.h"
#include "image.h"
#include "console.h"
#include "time.h"

using namespace spring;
using namespace spring::ui;

class Example : public Behaviour
{
private:
	bool enabled = true;
	MeshRenderer* sun;
public:
	void Awake() override
	{
		OnGUI();

		if (!enabled)
			return;
		ModelLoader loader = ModelLoader();
		loader.Load("res/model/fbx/747/747-400.fbx");

		Material* sunMaterial = new Material("res/shader/diffuse/diffuse.vs", "res/shader/diffuse/diffuse.fs");
		sunMaterial->cullface = Material::CullFace::Back;
		sun = new MeshRenderer(sunMaterial);
		sun->meshes = loader.meshes;
		sun->textures = loader.loadedTextures;
		sun->Init();
		sun->transform->position = Vector3::zero;
		sun->transform->scale = Vector3(5.0f);
		TextureLoader textureLoader;
		auto sunTexture = textureLoader.Load("res/model/fbx/747/747-400 texture.png");
		sun->material->shader->setTexture("MainTextureData.texture", sunTexture->textureId);
		sun->material->shader->setColor(MAIN_COLOR, Color(204, 204, 204, 128));
		sun->material->shader->setColor("Specular_Color", Color::white);
		sun->material->shader->setFloat("Specular_Intensity", 0.0f);
		sun->material->shader->setFloat("Specular_Attenuation", 64.0f);
	}

	Image* image;
	float rotateZ = 0.0f;

	void OnGUI() 
	{
		TextureLoader textureLoader;
		Texture* texture = textureLoader.Load("res/texture/spring.png",true);
		image = GUI::DrawImage(Rect(0.0f, 0.0f, 48, 48));
		image->texture = texture;
		image->material->depthTest = true;
		image->material->BlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		image->color = Color(255,255,255,128);
		image->rectTransform->SetPivot(Vector2(0.0f,1.0f));
		image->transform->SetPosition(Vector3(24.0f,Screen::height - 24.0f, 0.0f));
	}

	void Update() override
	{
		rotateZ += 1.0f;
		image->transform->SetEulerangle(Vector3(0.0f, 0.0f, rotateZ));
	}

	void Destroy() override
	{

	}
};