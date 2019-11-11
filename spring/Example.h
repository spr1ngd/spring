#pragma once
#include "springengine.h"
#include "gui.h"
#include "rect.h"
#include "image.h"
#include "console.h"
#include "time.h"
#include "fullscreenrenderer.h"

using namespace spring;
using namespace spring::ui;

class Example : public Behaviour
{
private:
	bool enabled = true;
	bool drawGround = true;
	bool drawFourFrame = false;
	MeshRenderer* aircraft;

	FrameBufferObject* framebuffer = FrameBufferObject::GenColorFramebuffer(Screen::width, Screen::height,0);

	Texture* texture = TextureLoader::Load("res/texture/grass.jpg", true);
	Texture* rawTexture = new Texture();

	Image* image; 
	Image* leftbttom;
	Image* rightbottom;

	MeshRenderer* ground;

public:
	void Awake() override
	{
		if (!enabled)
			return;

		if (this->drawGround)
			this->DrawGround();

		ModelLoader loader = ModelLoader();
		loader.Load("res/model/fbx/747/747-400.fbx");

		Material* mat = new Material("res/shader/diffuse/diffuse.vs", "res/shader/diffuse/diffuse.fs");
		mat->renderMode = Material::RenderMode::Fill;
		mat->CullFaceFunc(true);
		aircraft = new MeshRenderer(mat);
		aircraft->meshes = loader.meshes;
		aircraft->textures = loader.loadedTextures;
		aircraft->Init();
		aircraft->transform->position = Vector3::zero;
		aircraft->transform->scale = Vector3(5.0f);
		auto sunTexture = TextureLoader::Load("res/model/fbx/747/747-400 texture.png");
		aircraft->material->shader->setTexture("MainTextureData.texture", sunTexture->textureId);
		aircraft->material->shader->setColor(MAIN_COLOR, Color(204, 204, 204, 128));
		aircraft->material->shader->setColor("Specular_Color", Color::white);
		aircraft->material->shader->setFloat("Specular_Intensity", 0.0f);
		aircraft->material->shader->setFloat("Specular_Attenuation", 64.0f);

		// Camera::main->framebuffer = framebuffer;
		// rawTexture->textureId = framebuffer->buffer;
		 
		if (this->drawFourFrame) 
		{
			image = GUI::DrawImage(Rect(0.0f, 0.0f, (float)Screen::halfWidth, (float)Screen::halfHeight));
			image->material = new Material("res/shader/ui/default.vs", "res/shader/ui/default(detail).fs");
			image->material->AlphaBlendFunc();
			image->material->DepthTestFunc(false);
			image->color = Color(255, 255, 255, 255);
			image->transform->SetPosition(Vector3(Screen::halfWidth / 2.0f, Screen::halfHeight * 1.5f, 0.0f));
			image->material->shader->setTexture(SECONDARY_TEX, sunTexture->textureId);
			image->material->shader->setTexture(MAIN_TEX, texture->textureId);

			// leftbttom = GUI::DrawImage(Rect(0.0f, 0.0f, (float)Screen::halfWidth, (float)Screen::halfHeight));
			// leftbttom->material = new Material("res/shader/ui/default.vs", "res/shader/ui/postprocessing/edgedetecion.fs");
			// leftbttom->texture = rawTexture;
			// leftbttom->material->AlphaBlendFunc();
			// leftbttom->material->DepthTestFunc(false);
			// leftbttom->color = Color(255, 255, 255, 128);
			// leftbttom->transform->SetPosition(Vector3(Screen::halfWidth / 2.0f, Screen::halfHeight * 0.5f, 0.0f));
			// 
			// rightbottom = GUI::DrawImage(Rect(0.0f, 0.0f, (float)Screen::halfWidth, (float)Screen::halfHeight));
			// rightbottom->material = new Material("res/shader/ui/default.vs", "res/shader/ui/postprocessing/blur.fs");
			// rightbottom->texture = rawTexture;
			// rightbottom->material->AlphaBlendFunc();
			// rightbottom->material->DepthTestFunc(false);
			// rightbottom->color = Color(255, 255, 255, 128);
			// rightbottom->transform->SetPosition(Vector3(Screen::halfWidth * 1.5f, Screen::halfHeight * 0.5f, 0.0f));
		}
	}

	void DrawGround() 
	{
		ModelLoader* modelloader = new ModelLoader();
		modelloader->Load("res/model/obj/quad.obj");

		Material* groundMaterial = new Material("res/shader/diffuse/diffuse.vs","res/shader/diffuse/diffuse.fs");
		ground = new MeshRenderer(groundMaterial);
		ground->meshes = modelloader->meshes;
		ground->textures = modelloader->loadedTextures;
		ground->Init();

		ground->transform->SetScale(Vector3(50.0f));
		ground->transform->SetPosition(Vector3(0.0f,-2.0f,0.0f));
		ground->transform->SetEulerangle(Vector3(-90.0f,0.0f,0.0f));
		ground->material->shader->setColor(MAIN_COLOR,Color::white);
		Texture* groundTexture = TextureLoader::Load("res/texture/grass.jpg");
		auto whiteTexture = TextureLoader::GenPureWhiteTexture();
		ground->material->shader->setTexture("MainTextureData.texture", groundTexture->textureId);
		ground->material->shader->setColor("Specular_Color", Color::white);
		ground->material->shader->setFloat("Specular_Intensity", 0.0f);
		ground->material->shader->setFloat("Specular_Attenuation", 64.0f);
		ground->material->shader->setTilling("MainTextureData", Vector2(5, 5));
	}

	void OnPostRender() 
	{
		if (drawFourFrame)
		{
			/*rawTexture->textureId = Light::main->shadow->buffer;
			image->texture = rawTexture;*/
		}
	}


	float rotateY = 0.0f;

	void Update() override
	{
		rotateY += Timer::deltaTime * 15.0f;
		if (rotateY >= 360.0f)
			rotateY -= 360.0f;
		aircraft->transform->SetEulerangle(Vector3(0.0f, -rotateY,0.0f));
	}

	void Destroy() override
	{

	}
};