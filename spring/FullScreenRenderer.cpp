#include "fullscreenrenderer.h"
#include "light.h"
#include "screen.h"
#include "renderable.h"
#include "meshrenderer.h"

using namespace std;
using namespace spring;

std::vector<FullScreenRenderer*> FullScreenRenderer::renderers;

FullScreenRenderer::FullScreenRenderer()
{
	this->type = FullScreenRenderType::Color;
	this->Initialize();
}

FullScreenRenderer::FullScreenRenderer(FullScreenRenderType type) 
{
	this->type = type;
	this->Initialize();
}

void FullScreenRenderer::Initialize() 
{
	if (this->type == FullScreenRenderer::Color)  this->buffer = new FrameBufferObject(Screen::width, Screen::height, GL_COLOR_ATTACHMENT0, 0);
	else  this->buffer = new FrameBufferObject(Screen::width, Screen::height, GL_DEPTH_COMPONENT, 0);
	this->cullingMask = new LayerMask();
	this->cullingMask->set(new unsigned int[2]{ Layer::Default,Layer::Skybox });
	renderers.push_back(this);
}

void FullScreenRenderer::Destroy() 
{
	for (vector<FullScreenRenderer*>::iterator item = renderers.begin(); item != renderers.end(); item++)
	{
		FullScreenRenderer* fsr = *item;
		if (fsr == this)
		{
			renderers.erase(item);
			return;
		}
	}
}

void FullScreenRenderer::Render() 
{
	if (nullptr == this->material)
		return;
	//glBindFramebuffer(GL_FRAMEBUFFER, this->buffer->bufferId);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Light* light = Light::main;
	auto view = glm::lookAt(
		glm::vec3(light->transform->position.x,light->transform->position.y,light->transform->position.z),
		glm::vec3(0.0f,0.0f,0.0f),
		glm::vec3(light->transform->up.x,light->transform->up.y,light->transform->up.z));
	auto projection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 1.0f, 10.0f);
	//glBindFramebuffer(GL_FRAMEBUFFER,0);
	/*glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);*/
}