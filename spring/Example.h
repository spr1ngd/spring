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

		Material* sunMaterial = new Material("res/shader/diffuse/diffuse.vs", "res/shader/diffuse/diffuse.fs");
		sun = new MeshRenderer(sunMaterial);
		sun->meshes = loader.meshes;
		sun->textures = loader.loadedTextures;
		sun->Init();
		sun->transform->position = Vector3::zero;
		sun->transform->scale = Vector3(5.0f);
		auto sunTexture = TextureLoader::Load("res/model/fbx/747/747-400 texture.png");
		// sun->material->shader->setTexture("MainTextureData.texture", sunTexture->textureId);
		sun->material->shader->setColor(MAIN_COLOR, Color(204, 204, 204, 128));
		sun->material->shader->setColor("Specular_Color", Color::white);
		sun->material->shader->setFloat("Specular_Intensity", 0.0f);
		sun->material->shader->setFloat("Specular_Attenuation", 64.0f);

		Camera::main->cullingMask->remove(Layer::UI);
		Camera::main->framebuffer = framebuffer;
		rawTexture->textureId = framebuffer->colorbuffer;

		Texture* texture = TextureLoader::Load("res/screen.bmp", true);
		image = GUI::DrawImage(Rect(0.0f, 0.0f, Screen::halfWidth, Screen::halfHeight));
		// this->image->texture = texture;
		// framebuffer->colorbuffer = texture->textureId;
		image->material->DepthTestFunc(false);
		image->color = Color(255, 255, 255, 255);
		// image->rectTransform->SetPivot(Vector2(0.0f, 1.0f));
		image->transform->SetPosition(Vector3(Screen::halfWidth,Screen::halfHeight, 0.0f));
	}

	void OnPostRender() override
	{
		glBindFramebuffer(GL_FRAMEBUFFER, this->framebuffer->bufferId);
		unsigned char* pixels = new unsigned char[Screen::width * Screen::height * 4];
		glReadPixels(0, 0, Screen::width, Screen::height, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
		TextureLoader::SaveToBMP("res/screen.bmp", Screen::width, Screen::height, pixels);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		rawTexture->textureId = framebuffer->colorbuffer;
		this->image->texture = rawTexture;
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