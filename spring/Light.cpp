
#include "glm/glm.hpp"
#include "light.h"
#include "screen.h"
#include "camera.h"
#include "meshrenderer.h"
#include "instancedrenderer.h"
#include "graphic.h"

using namespace std;
using namespace spring;

vector< Light*> Light::lights;
Light* Light::main;
Material* Light::depthMaterial;
Material* Light::tMaterial;
Material* instanceDepthMaterial;

Light::Light()
{
	this->type = Light::Type::Directional;
	this->renderMode = Light::RenderMode::Pixel;
	this->color = Color::white;
	this->intensity = 1.0f;
	this->shadowType = ShadowType::HardShadow;

	// set the first light as scene main light source
	if (lights.size() == 0)
		Light::main = this;

	if (nullptr == depthMaterial)
	{
		// depthMaterial = new Material(Shader::Load("shadow/shadow.vs", "shadow/shadow.fs"));
		depthMaterial = new Material(Shader::Load("shadow/shadow(newer).vs", "shadow/shadow.fs"));
		instanceDepthMaterial = new Material(Shader::Load("shadow/shadow(instance).vs", "shadow/shadow.fs"));

		tMaterial = new Material(Shader::Load("fullscreen/fullscreen.vs", "shadow/shadow(display).fs"));
	}
	Light::lights.push_back(this);
}

void Light::CastShadow() 
{
	unsigned int shadowMapSize = 1024;
	// depth->CullFaceFunc(true, GL_FRONT);
	for (Light* light : Light::lights)
	{
		glViewport(0, 0, shadowMapSize, shadowMapSize);
		if (light->shadowType == Light::NoShadow)
			continue;
		if (light->shadow == nullptr)
		{
			// light->shadow = FrameBuffer::GenDepthFramebuffer(Screen::width, Screen::height);
			light->shadow = new FrameBuffer(shadowMapSize, shadowMapSize);
			light->shadow->colorFormat = ColorFormat::Shadow;
			light->shadow->Initialize();

			light->tbuffer = new FrameBuffer(shadowMapSize, shadowMapSize);
			light->tbuffer->colorFormat = ColorFormat::RGB24;
			light->tbuffer->Initialize();
		}
		// todo : expose those parameters
		glm::mat4 projection = glm::ortho(-light->size, light->size, -light->size, light->size,light->zNear, light->zFar);
		glm::mat4 view = glm::lookAt(
			glm::vec3(light->transform->position.x,light->transform->position.y,light->transform->position.z),
			glm::vec3(0.0f,0.0f,0.0f),
			glm::vec3(0.0f,1.0f,0.0));
		light->lightSpaceMatrix = projection * view;

		light->shadow->Bind();
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		Renderable::Draw(light->layers.layers, [&](MeshRenderer* renderer)
			{
				if (renderer->material->castShadow)
				{
					Material* srcMaterial = renderer->material;
					if( renderer->enableGPUInstance ) 
						renderer->material = instanceDepthMaterial;
					else
						renderer->material = depthMaterial;
					// todo : make camera culling mask equal with light.
					renderer->Render(view,projection);
					renderer->material = srcMaterial;
				}
			});
		light->shadow->Unbind();
		Graphic::Blit(*light->shadow, *light->tbuffer,*tMaterial); 
	}
	glViewport(0, 0, Screen::width,Screen::height);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}