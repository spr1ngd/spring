#include "postprocessing.h"
#include "console.h"
#include "graphic.h"

using namespace spring;

class::spring::PostProcessing* PostProcessing::postprocessing;
FrameBuffer* PostProcessing::outputFramebuffer;

Material* outputMaterial;

PostProcessing::PostProcessing()
{
	this->antiAliasing = new AntiAliasing();
	this->bloom = new Bloom();
	this->toneMapping = new ToneMapping();
	this->toneMapping->exposure = 1.0f;
	this->outline = new Outline();
	this->outline->outlineMaterial = new Material(Shader::Load("postprocessing/outline/outline.vs","postprocessing/outline/outline.fs"));
	this->outline->outlineBlendMaterial = new Material(Shader::Load("fullscreen/fullscreen.vs","postprocessing/outline/outline(blend).fs"));
	this->outline->outputMateiral = new Material(Shader::Load("fullscreen/fullscreen.vs","postprocessing/add.fs"));

	this->outline->buffer = new FrameBuffer(Screen::width,Screen::height);
	this->outline->buffer->Initialize();

	this->outline->originBuffer = new FrameBuffer(Screen::width,Screen::height);
	this->outline->originBuffer->Initialize();

	this->outline->blendBuffer = new FrameBuffer(Screen::width, Screen::height);
	this->outline->blendBuffer->Initialize();

	this->outline->outputBuffer = new FrameBuffer(Screen::width,Screen::height);
	this->outline->outputBuffer->Initialize();
}

void PostProcessing::Awake() 
{

}

void PostProcessing::Update() 
{

}

void PostProcessing::Destroy() 
{

}

void PostProcessing::Initialize() 
{ 
	if (this->enabled == false)
		return;
	outputFramebuffer = new FrameBuffer(Screen::width,Screen::height);
	outputFramebuffer->Initialize();
	outputMaterial = new Material(Shader::Load("fullscreen/fullscreen.vs", "fullscreen/fullscreen.fs"));

	// if (this->antiAliasing->enabled)
	// {
	// 	this->srcFramebuffer = FrameBuffer::GenMSColorFramebuffer(Screen::width, Screen::height, this->antiAliasing->samples);
	// }

	if (this->bloom->enable)
	{
		this->bloom->material = new Material(Shader::Load("fullscreen/fullscreen.vs", "postprocessing/bloom/bloom.fs")); // extract hdr portion
		this->bloom->gaussianBlurMaterial = new Material(Shader::Load("fullscreen/fullscreen.vs","postprocessing/bloom/gaussianblur.fs")); // use gaussian blur post hdr portion
		this->bloom->bloomAddMaterial = new Material(Shader::Load("fullscreen/fullscreen.vs","postprocessing/bloom/bloomadd.fs")); // blend hdr portion and normal buffer
		this->bloom->material->shader->enableLighting = false;
		this->bloom->buffer = new FrameBuffer(Screen::width,Screen::height,ColorFormat::RGB16Float,2);
		this->bloom->buffer->Initialize();

		this->bloom->bloomBuffer = new FrameBuffer(Screen::width,Screen::height, ColorFormat::RGB16Float);
		this->bloom->bloomBuffer->Initialize();

		this->bloom->bloomTemp = new FrameBuffer(Screen::width,Screen::height, ColorFormat::RGB16Float);
		this->bloom->bloomTemp->Initialize();
	}

	if (this->toneMapping->enable) 
	{
		this->toneMapping->material = new Material(Shader::Load("fullscreen/fullscreen.vs","postprocessing/tonemapping/tonemapping.fs"));
		this->toneMapping->material->shader->enableLighting = false;
		this->toneMapping->buffer = new FrameBuffer(Screen::width,Screen::height);
		this->toneMapping->buffer->Initialize();
	}

	this->srcFramebuffer = new FrameBuffer(Screen::width,Screen::height, ColorFormat::RGBA16Float);
	this->srcFramebuffer->depthbuffer = FrameBuffer::OnlyDepth;
	this->srcFramebuffer->Initialize();

	this->dstFramebuffer = new FrameBuffer(Screen::width,Screen::height, ColorFormat::RGBA16Float);
	this->dstFramebuffer->Initialize();

	Camera::main->framebuffer = this->srcFramebuffer;
}

void PostProcessing::Preprocess() 
{
	if (this->enabled == false)
		return;
	Camera::main->framebuffer = this->srcFramebuffer;
}

void PostProcessing::Process() 
{
	if (this->enabled == false)
		return;

	this->Blit(this->srcFramebuffer,this->dstFramebuffer);
	FrameBuffer* transfer = this->dstFramebuffer;

	// bloom 
	if (this->bloom->enable)
	{
		this->bloom->material->shader->setFloat("threshold",this->bloom->threshold);
		this->bloom->material->shader->setColor(MAIN_COLOR,this->bloom->color);
		this->Blit(transfer, this->bloom->buffer, this->bloom->material);
		transfer = this->bloom->buffer;

		bool firstTransfer = true;
		bool hSample = true;
		for (int i = 0; i < 10; i++) 
		{
		 	this->bloom->gaussianBlurMaterial->shader->setBool("hSample",hSample);
			if (firstTransfer)
				this->Blit(transfer, this->bloom->bloomBuffer, this->bloom->gaussianBlurMaterial, 1);
			else
				this->Blit(hSample ? this->bloom->bloomTemp : this->bloom->bloomBuffer,
					hSample ? this->bloom->bloomBuffer : this->bloom->bloomTemp,
					this->bloom->gaussianBlurMaterial);
			firstTransfer = false;
			transfer = this->bloom->bloomTemp;
		 	hSample = !hSample;
		}

		this->bloom->bloomAddMaterial->shader->setTexture("BrightTexture",transfer->GetBuffer());
		this->Blit(this->bloom->buffer, this->bloom->bloomBuffer, this->bloom->bloomAddMaterial, 0);
		transfer = this->bloom->bloomBuffer;
		// blend src and bright area
	}

	// outline
	if (this->outline->enable)
	{
		this->outline->outlineBlendMaterial->shader->setTexture("outlineTexture", this->outline->buffer->GetBuffer());
		this->Blit(this->outline->originBuffer, this->outline->blendBuffer, this->outline->outlineBlendMaterial);

		this->outline->outputMateiral->shader->setTexture("addTexture", this->outline->blendBuffer->GetBuffer());
		this->Blit(transfer, this->outline->outputBuffer, this->outline->outputMateiral);
		transfer = this->outline->outputBuffer;
	}

	// tone mapping
	if (this->toneMapping->enable)
	{
		this->toneMapping->material->shader->setFloat("exposure",this->toneMapping->exposure);
		this->Blit(transfer, this->toneMapping->buffer, this->toneMapping->material);
		transfer = this->toneMapping->buffer;
	}

	// blit to final framebuffer and render it to scene editor window (hdr framebuffer -> general color framebuffer)
	this->Blit(transfer, outputFramebuffer);

	// ÊÖ¶¯ÅÅÐò
	 
	// add vignette at finally
	PostProcessingFX* vignette = this->GetFX(PostProcessingVignette);
	if (nullptr != vignette)
	{
		vignette->Process(*outputFramebuffer,);
	}
}

void PostProcessing::Blit(FrameBuffer* src,FrameBuffer* dst)
{
	Graphic::Blit(*src, *dst);
}

void PostProcessing::Blit(FrameBuffer* src, FrameBuffer* dst, Material* material) 
{
	Graphic::Blit(*src, *dst, *material);
}

void PostProcessing::Blit(FrameBuffer* src, FrameBuffer* dst, Material* material,unsigned int attachment)
{
	Graphic::Blit(*src, *dst, *material, attachment);
}