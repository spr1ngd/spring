#include "postprocessing.h"
#include "console.h"

using namespace spring;

class::spring::PostProcessing* PostProcessing::postprocessing;
FrameBufferObject* PostProcessing::outputFramebuffer;

Material* outputMaterial;

PostProcessing::PostProcessing()
{
	this->antiAliasing = new AntiAliasing();
	this->bloom = new Bloom();
	this->toneMapping = new ToneMapping();
	this->toneMapping->exposure = 1.0f;
}

void PostProcessing::Initialize() 
{
	if (this->enabled == false)
		return;
	outputFramebuffer = FrameBufferObject::GenColorFramebuffer(Screen::width, Screen::height, 0);
	outputMaterial = new Material("res/shader/fullscreen/fullscreen.vs", "res/shader/fullscreen/fullscreen.fs");
	
	this->fsRenderer = new FullScreenRenderer();
	this->fsRenderer->Init();

	// if (this->antiAliasing->enabled)
	// 	this->srcFramebuffer = FrameBufferObject::GenMSColorFramebuffer(this->antiAliasing->samples, Screen::width, Screen::height);

	if (this->bloom->enable)
	{
		this->bloom->material = new Material(Shader::Load("fullscreen/fullscreen.vs", "postprocessing/bloom/bloom.fs"));
		this->bloom->gaussianBlurMaterial = new Material(Shader::Load("fullscreen/fullscreen.vs","postprocessing/bloom/gaussianblur.fs"));
		this->bloom->material->shader->enableLighting = false;
		this->bloom->buffer = FrameBufferObject::GenHDRColorFramebuffer(Screen::width, Screen::height, 0, 2);
		this->bloom->bloomBuffer = FrameBufferObject::GenSingleHDRColorFramebuffer(Screen::width,Screen::height,0);
	}

	if (this->toneMapping->enable) 
	{
		this->toneMapping->material = new Material(Shader::Load("fullscreen/fullscreen.vs","postprocessing/tonemapping/tonemapping.fs"));
		this->toneMapping->material->shader->enableLighting = false;
		this->toneMapping->buffer = FrameBufferObject::GenColorFramebuffer(Screen::width, Screen::height, 0);
	}

	this->srcFramebuffer = FrameBufferObject::GenSingleHDRColorFramebuffer(Screen::width, Screen::height, 0);
	this->dstFramebuffer = FrameBufferObject::GenSingleHDRColorFramebuffer(Screen::width, Screen::height, 0);
	Camera::main->framebuffer = this->srcFramebuffer;
}

void PostProcessing::Preprocess() 
{
	Camera::main->framebuffer = this->srcFramebuffer;
}

void PostProcessing::Process() 
{
	if (this->enabled == false)
		return;

	this->Blit(this->srcFramebuffer,this->dstFramebuffer);
	FrameBufferObject* transfer = this->dstFramebuffer;

	// bloom 
	if (this->bloom->enable)
	{
		this->Blit(transfer, this->bloom->buffer, this->bloom->material);
		transfer = this->bloom->buffer;

		FrameBufferObject* temp = FrameBufferObject::GenSingleHDRColorFramebuffer(Screen::halfHeight, Screen::height, 0);
		bool hSample = true;
		for (int i = 0; i < 10; i++) 
		{
			this->bloom->gaussianBlurMaterial->shader->setBool("hSample",hSample);
			this->Blit(hSample ? temp : this->bloom->bloomBuffer, hSample ? this->bloom->bloomBuffer : temp, this->bloom->gaussianBlurMaterial);
			hSample = !hSample;
		}
		transfer = temp;
		temp->Delete();
		delete temp;
	}

	// tone mapping
	if (this->toneMapping->enable)
	{
		this->toneMapping->material->shader->setFloat("exposure",this->toneMapping->exposure);
		this->Blit(transfer, this->toneMapping->buffer, this->toneMapping->material);
		transfer = this->toneMapping->buffer;
	}

	// blit to final framebuffer and render it to scene editor window (hdr framebuffer -> general color framebuffer)
	this->Blit(transfer,outputFramebuffer);
}

void PostProcessing::Blit(FrameBufferObject* src,FrameBufferObject* dst)
{
	glBindFramebuffer(GL_READ_FRAMEBUFFER, src->framebufferId);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, dst->framebufferId);
	glBlitFramebuffer(0, 0, src->width, src->height, 0, 0, dst->width, dst->height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void PostProcessing::Blit(FrameBufferObject* src, FrameBufferObject* dst, Material* material) 
{
	this->fsRenderer->material = material;
	this->fsRenderer->material->shader->setTexture(MAIN_TEX, src->buffer);// 这里根据是否运行使用MTR取不同的buffer attachment

	Camera::current = Camera::main;
	Camera::current->framebuffer = dst;
	Camera::current->framebuffer->Bind();
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	unsigned int* postProcessingLayer = new unsigned int[1]{ Layer::PostProcessing };
	Renderable::Draw(1, postProcessingLayer);
	Camera::current->framebuffer->Unbind();
	glClearColor(0.1f,0.4f,0.7f,1.0f);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	delete[] postProcessingLayer;
}