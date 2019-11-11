
#include <glm/glm.hpp>
#include "light.h"
#include "screen.h"
#include "camera.h"
#include "meshrenderer.h"

using namespace std;
using namespace spring;

vector< Light*> Light::lights;
Light* Light::main;

Light::Light()
{
	this->type = Light::Type::Directional;
	this->renderMode = Light::RenderMode::Pixel;
	this->color = Color::white;
	this->intensity = 1.0f;
	this->cullingMask = new LayerMask();
	this->cullingMask->set(new unsigned int[1] {0x0001});
	this->shadowType = ShadowType::HardShadow;

	if (lights.size() == 0)
		Light::main = this;
	Light::lights.push_back(this);
}

void Light::CastShadow() 
{
	Camera* camera = Camera::main;
	Camera::Type srcCameraType = camera->cameraType;
	Vector3 srcPosition = camera->transform->GetPosition();
	Vector3 srcEulerangle = camera->transform->GetEulerangle();
	camera->cameraType = Camera::Type::Orthographic;
	Material* depth = new Material("res/shader/shadow/shadow.vs", "res/shader/shadow/shadow.fs");
	for (Light* light : Light::lights)
	{
		if (light->shadowType == Light::NoShadow)
			continue;
		if (light->shadow == nullptr)
			light->shadow = FrameBufferObject::GenDepthFramebuffer(Screen::width, Screen::height);

		camera->transform->SetPosition(light->transform->GetPosition());
		camera->transform->SetEulerangle(light->transform->GetEulerangle());
		camera->Update();// update camera's view matrix and projection matrix.
		light->lightSpaceMatrix = camera->GetProjectionMatrix() * camera->GetViewMatrix();

		glBindFramebuffer(GL_FRAMEBUFFER,light->shadow->bufferId);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		Renderable::Draw(new unsigned int[1]{ 0x0001 }, [&](MeshRenderer* renderer)
			{
				Material* srcMaterial = renderer->material;
				renderer->material = depth;
				renderer->Render(camera);
				renderer->material = srcMaterial;
			});
		glBindFramebuffer(GL_FRAMEBUFFER,0);
	}
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	camera->cameraType = srcCameraType;
	camera->transform->SetPosition(srcPosition);
	camera->transform->SetEulerangle(srcEulerangle);
}