#include "graphic.h"
#include "springengine.h"
#include "fullscreenrenderer.h"

using namespace spring;

FullScreenRenderer* Graphic::fsRenderer;

void Graphic::Initialize()
{
	if (nullptr == Graphic::fsRenderer) 
	{
		GameObject* renderer = new GameObject("FullScreenRenderer(Graphic_Internal)");
		renderer->layer = Layer::PostProcessing;
		renderer->flags |= HideFlags::HideFlags_HideInHierarchyWindow;
		Graphic::fsRenderer = renderer->AddNode<FullScreenRenderer>();
		Graphic::fsRenderer->Initialize();
	}
}

void Graphic::Blit(FrameBuffer& source, FrameBuffer& destination) 
{
	Graphic::Initialize();
	glBindFramebuffer(GL_READ_FRAMEBUFFER, source.framebufferId);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, destination.framebufferId);
	glBlitFramebuffer(0, 0, source.width, source.height, 0, 0, destination.width, destination.height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Graphic::Blit(FrameBuffer& source, FrameBuffer& destination, Material& material) 
{
	Graphic::Initialize();
	Graphic::fsRenderer->material = &material;
	Graphic::fsRenderer->material->shader->setTexture(MAIN_TEX, source.GetBuffer());

	Camera::current = Camera::main;
	auto currentFramebuffer = Camera::current->framebuffer;
	Camera::current->framebuffer = &destination;
	Camera::current->framebuffer->Bind();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.1f, 0.4f, 0.7f, 1.0f);
	Renderable::Draw(Layer::PostProcessing);
	Camera::current->framebuffer->Unbind();
	Camera::current->framebuffer = currentFramebuffer;
}

void Graphic::Blit(FrameBuffer& source, FrameBuffer& destination, Material& material, unsigned int attachment) 
{
	Graphic::Initialize();
	Graphic::fsRenderer->material = &material;
	Graphic::fsRenderer->material->shader->setTexture(MAIN_TEX, source.GetBuffer(attachment));

	Camera::current = Camera::main;
	auto currentFramebuffer = Camera::current->framebuffer;
	Camera::current->framebuffer = &destination;
	Camera::current->framebuffer->Bind();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.1f, 0.4f, 0.7f, 1.0f);
	Renderable::Draw(Layer::PostProcessing);
	Camera::current->framebuffer->Unbind();
	Camera::current->framebuffer = currentFramebuffer;
}