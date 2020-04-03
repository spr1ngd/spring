
#include "glm/glm.hpp"
#include "light.h"
#include "screen.h"
#include "camera.h"
#include "meshrenderer.h"
#include "instancedrenderer.h"

using namespace std;
using namespace spring;

vector< Light*> Light::lights;
Light* Light::main;
Material* Light::depthMaterial;
Material* instanceDepthMaterial;

Light::Light()
{
	this->type = Light::Type::Directional;
	this->renderMode = Light::RenderMode::Pixel;
	this->color = Color::white;
	this->intensity = 1.0f;
	this->cullingMask = new LayerMask();
	this->cullingMask->set(Layer::Default);
	this->shadowType = ShadowType::HardShadow;

	if (lights.size() == 0)
		Light::main = this;
	Light::lights.push_back(this);

	if (nullptr == depthMaterial)
	{
		depthMaterial = new Material(Shader::Load("shadow/shadow.vs", "shadow/shadow.fs"));
		instanceDepthMaterial = new Material(Shader::Load("shadow/shadow(instance).vs", "shadow/shadow.fs"));
	}
}

void Light::CastShadow() 
{
	// todo : how to promote shadow map resolution
	Camera* camera = Camera::main;
	Camera::Type srcCameraType = camera->cameraType;
	Vector3 srcPosition = camera->transform->GetPosition();
	Vector3 srcEulerangle = camera->transform->GetEulerangle();
	camera->cameraType = Camera::Type::Orthographic;
	// depth->CullFaceFunc(true, GL_FRONT);
	for (Light* light : Light::lights)
	{
		if (light->shadowType == Light::NoShadow)
			continue;
		if (light->shadow == nullptr)
		{
			// light->shadow = FrameBuffer::GenDepthFramebuffer(Screen::width, Screen::height);
			light->shadow = new FrameBuffer(Screen::width, Screen::height);
			light->shadow->colorFormat = ColorFormat::Shadow;
			light->shadow->Initialize();
		}

		camera->transform->SetPosition(light->transform->GetPosition());
		camera->transform->SetEulerangle(light->transform->GetEulerangle());
		camera->Update();// update camera's view matrix and projection matrix.

		// todo : fixed light space matrix
		light->lightSpaceMatrix = camera->GetProjectionMatrix() * camera->GetViewMatrix();

		light->shadow->Bind();
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		Renderable::Draw(1,new unsigned int[1]{ 0x0001 }, [&](MeshRenderer* renderer)
			{
				if (renderer->material->castShadow)
				{
					Material* srcMaterial = renderer->material;
					if( renderer->enableGPUInstance ) renderer->material = instanceDepthMaterial;
					else renderer->material = depthMaterial;
					renderer->Render(camera);
					renderer->material = srcMaterial;
				}
			});
		light->shadow->Unbind();
	}
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	camera->cameraType = srcCameraType;
	camera->transform->SetPosition(srcPosition);
	camera->transform->SetEulerangle(srcEulerangle);
}