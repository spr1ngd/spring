#pragma once
#include "springengine.h"
#include "gui.h"
#include "rect.h"
#include "image.h"
#include "console.h"
#include "time.h"
#include <stdio.h>
#include "selection.h"

using namespace spring;
using namespace spring::ui;

class Example : public Behaviour
{
public:
	bool enabled = false;

private:
	bool drawGround = true;
	bool drawFourFrame = true;
	bool drawText = true;
	bool drwaAirCraftNormal = true;

	bool rotate = false;
	MeshRenderer* aircraft;
	MeshRenderer* aircraftNormal;

	Texture* texture = nullptr;

	Image* image; 
	Image* leftbttom;
	Image* rightbottom;

	Text* springEngine;
	Text* text;

	MeshRenderer* ground;

public:
	void Awake() override
	{
		if (!enabled)
			return;
		texture = TextureLoader::Load("res/texture/grass.jpg", true);
		if (this->drawGround)
			this->DrawGround();

		Mesh& mesh = ModelLoader::LoadMeshFromFile("fbx/747/747-400.fbx");
		Material* mat = new Material(Shader::Load("diffuse/diffuse.vs", "diffuse/diffuse.fs"));
		mat->renderMode = Material::RenderMode::Fill;
		mat->CullFaceFunc(true);
		aircraft = new MeshRenderer(mat);
		aircraft->name = "aircraft";
		aircraft->mesh = &mesh;
		aircraft->Initialize();
		aircraft->transform->position = Vector3::zero;
		aircraft->transform->scale = Vector3(5.0f);
		auto sunTexture = TextureLoader::Load("res/model/fbx/747/747-400 texture.png");
		aircraft->material->shader->setTexture("MainTextureData.texture", sunTexture->textureId);
		aircraft->material->shader->setColor(MAIN_COLOR, Colorf(5.0f, 5.0f, 5.0f, 1.0f ));
		/*aircraft->material->shader->setColor("Specular_Color", Color::white);
		aircraft->material->shader->setFloat("Specular_Intensity", 0.0f);
		aircraft->material->shader->setFloat("Specular_Attenuation", 64.0f);*/

		// aircraft normal visualization.
		if (drwaAirCraftNormal) 
		{
			Material* normalMat = new Material(Shader::Load("diffuse/diffuse.vs", "diffuse/diffuse.fs"));
			normalMat->renderMode = Material::RenderMode::Fill;
			normalMat->CullFaceFunc(true);
			aircraftNormal = new MeshRenderer(normalMat);
			aircraftNormal->mesh = &mesh;
			aircraftNormal->Initialize();
			aircraftNormal->transform->position = Vector3(6.0f,0.0f,0.0f);
			aircraftNormal->transform->scale = Vector3(5.0f);
			aircraftNormal->material->shader->setTexture("MainTextureData.texture", sunTexture->textureId);
			aircraftNormal->material->shader->setColor(MAIN_COLOR, Color(204, 204, 204, 128));
			aircraftNormal->material->shader->setColor("Specular_Color", Color::white);
			aircraftNormal->material->shader->setFloat("Specular_Intensity", 0.0f);
			aircraftNormal->material->shader->setFloat("Specular_Attenuation", 64.0f);
		}
	
		if (this->drawFourFrame) 
		{
			image = GUI::DrawImage(Rect(0.0f, 0.0f, (float)Screen::halfWidth, (float)Screen::halfHeight));
			image->material = new Material(Shader::Load("ui/default.vs", "ui/default.fs"));
			// image->texture = texture;
			image->material->AlphaBlendFunc();
			image->material->DepthTestFunc(false);
			image->color = Color(255, 255, 255, 255);
			image->transform->SetPosition(Vector3(Screen::halfWidth / 2.0f, Screen::halfHeight * 1.5f, 0.0f));
		
			//image->material->shader->setTexture(SECONDARY_TEX, sunTexture->textureId);

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

		if (this->drawText) 
		{
			this->springEngine = GUI::DrawText(Rect(0.0f, 0.0f, 300.0f, 48.0f));
			this->springEngine->name = "SpringEngine";
			this->springEngine->font = new Font("arial.ttf");
			this->springEngine->material = new Material(Shader::Load("ui/font.vs", "ui/font.fs"));
			this->springEngine->material->AlphaBlendFunc();
			this->springEngine->material->DepthTestFunc(false);
			this->springEngine->color = Color::white;
			this->springEngine->transform->SetPosition(Vector3(0.0f + 150.0f, Screen::height - 48.0f, 0.0f));
			this->springEngine->color = Color(255,116,0,180);
			// this->springEngine->richText = true;
			this->springEngine->SetText("<b>S</b>pring <b>E</b>ngine.");

			this->text = GUI::DrawText(Rect(0.0f, 0.0f, 120, 24.0f));
			this->text->name = "FPS";
			this->text->font = new Font("arial.ttf");
			this->text->material = new Material(Shader::Load("ui/font.vs", "ui/font.fs"));
			this->text->material->AlphaBlendFunc();
			this->text->material->DepthTestFunc(false);
			this->text->color = Color(93,221,221,255);
			this->text->transform->SetLocalScale(Vector3(0.5f));
			this->text->transform->SetPosition(Vector3(Screen::width - 50.0f, Screen::height - 24.0f, 0.0f));
		}
	}

	void DrawGround() 
	{
		Material* groundMaterial = new Material(Shader::Load("diffuse/diffuse.vs", "diffuse/diffuse.fs"));
		ground = new MeshRenderer(groundMaterial);
		Mesh& mesh = ModelLoader::LoadMeshFromFile("obj/quad.obj");
		ground->mesh = &mesh;
		ground->Initialize();

		ground->transform->SetLocalScale(Vector3(50.0f));
		ground->transform->SetPosition(Vector3(0.0f,-2.0f,0.0f));
		ground->transform->SetEulerangle(Vector3(-90.0f,0.0f,0.0f));
		ground->material->shader->setColor(MAIN_COLOR,Color::white);
		Texture* groundTexture = TextureLoader::Load("res/texture/grass.jpg");
		auto whiteTexture = TextureLoader::CreatePureWhiteTexture();
		ground->material->shader->setTexture("MainTextureData.texture", groundTexture->textureId);
		ground->material->shader->setColor("Specular_Color", Color::white);
		ground->material->shader->setFloat("Specular_Intensity", 0.0f);
		ground->material->shader->setFloat("Specular_Attenuation", 64.0f);
		ground->material->shader->setTilling("MainTextureData", Vector2(5, 5));
	}

	void OnPostRender() 
	{
		if (!enabled)
			return;
		if (drawFourFrame)
		{
			// rawTexture->textureId = Light::main->shadow->buffer;
			// image->material->shader->setTexture(MAIN_TEX, Light::main->shadow->buffer);

			// Camera::main->transform->SetPosition(Light::main->transform->GetPosition());
			// Camera::main->transform->SetEulerangle(Light::main->transform->GetEulerangle());
		}
	}

	float rotateY = 0.0f;
	float characterSpace = 0.0f;

	void Update() override
	{
		if (!enabled)
			return;
		if (rotate)
		{
			rotateY += Timer::deltaTime * 15.0f;
			if (rotateY >= 360.0f)
				rotateY -= 360.0f;
			aircraft->transform->SetEulerangle(Vector3(0.0f, -rotateY, 0.0f));
			/*if( nullptr != this->aircraftNormal )
				aircraftNormal->transform->SetEulerangle(Vector3(0.0f, -rotateY, 0.0f));

			characterSpace += Timer::deltaTime * 5.0f;
			if (characterSpace > 20.0f)
				characterSpace -= 40.0f;*/
		}

		if (this->drawText)
		{
			char buf[16];
			sprintf_s(buf, "%s:%d", "FPS", FPS::fps);
			this->text->SetText(buf);
		}
	}

	void Destroy() override
	{

	}
};