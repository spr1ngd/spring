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
	MeshRenderer* aircraft;
	FrameBufferObject* framebuffer = FrameBufferObject::GenColorFramebuffer(Screen::width, Screen::height,0);
	Texture* rawTexture = new Texture();

	Image* image;
	float rotateZ = 0.0f;

public:
	void Awake() override
	{
		OnGUI();

		if (!enabled)
			return;
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

		Camera::main->cullingMask->remove(Layer::UI);
		Camera::main->framebuffer = framebuffer;
		rawTexture->textureId = framebuffer->colorbuffer;
		 
		Texture* texture = TextureLoader::Load("res/screen.bmp", true);
		image = GUI::DrawImage(Rect(0.0f, 0.0f, Screen::width, Screen::height));
		image->texture = rawTexture;
		image->material->DepthTestFunc(false);
		image->color = Color(255, 255, 255, 255);
		// image->rectTransform->SetPivot(Vector2(0.0f, 1.0f));
		image->transform->SetPosition(Vector3(Screen::halfWidth, Screen::halfHeight, 0.0f));
	}

	void OnPostRender() override
	{ 

	}

	void Update() override
	{
		rotateZ += 1.0f;
		// image->transform->SetEulerangle(Vector3(0.0f, 0.0f, rotateZ));
	}

	void Destroy() override
	{

	}
};