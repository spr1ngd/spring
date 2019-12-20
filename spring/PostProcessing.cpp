#include "postprocessing.h"
#include "console.h"

using namespace spring;

PostProcessing::PostProcessing()
{
	this->antiAliasing = new AntiAliasing();
	this->bloom = new Bloom();
}

void PostProcessing::Blit() 
{
	glBindFramebuffer(GL_READ_FRAMEBUFFER, this->srcFramebuffer->bufferId);
	// glBindFramebuffer(GL_READ_FRAMEBUFFER, this->srcFramebuffer->buffers[0]);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, this->dstFramebuffer->bufferId);
	glBlitFramebuffer(0, 0, this->srcFramebuffer->width, this->srcFramebuffer->height, 0, 0, this->dstFramebuffer->width, this->dstFramebuffer->height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
	glBindFramebuffer(GL_FRAMEBUFFER,0);
}

void PostProcessing::PreProcess() 
{
	if (this->enabled == false)
		return;
	this->fsRenderer = new FullScreenRenderer();
	this->fsRenderer->Init();
	if (this->antiAliasing->enabled)
		this->srcFramebuffer = FrameBufferObject::GenMSColorFramebuffer(this->antiAliasing->samples, Screen::width, Screen::height);
	else if (this->bloom->enabled)
		this->srcFramebuffer = FrameBufferObject::GenHDRColorFramebuffer(Screen::width,Screen::height,1,0);
	else 
		this->srcFramebuffer = FrameBufferObject::GenColorFramebuffer(Screen::width, Screen::height, 0);
	this->dstFramebuffer = FrameBufferObject::GenColorFramebuffer(Screen::width, Screen::height, 0);
	Camera::main->framebuffer = this->srcFramebuffer;
}

void PostProcessing::Process() 
{
	if (this->enabled == false)
		return;
	if (nullptr == this->fsRenderer)
		return;
	this->Blit();
	this->fsRenderer->material->shader->setTexture(MAIN_TEX, this->srcFramebuffer->bufferId);
	//this->fsRenderer->material->shader->setTexture(MAIN_TEX, this->srcFramebuffer->buffers[0]);
	unsigned int* postProcessingLayer = new unsigned int[1]{Layer::PostProcessing};
	Camera::current = Camera::main;
	Renderable::Draw(1, postProcessingLayer);
	delete[] postProcessingLayer;
}