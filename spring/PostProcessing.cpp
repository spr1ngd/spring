#include "postprocessing.h"
#include "console.h"

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
	// this->outline->buffer = FrameBuffer::GenSingleHDRColorFramebuffer(Screen::width,Screen::height,0);

	this->outline->buffer = new FrameBuffer(Screen::width,Screen::height);
	this->outline->buffer->Initialize();

	// this->outline->originBuffer = FrameBuffer::GenSingleHDRColorFramebuffer(Screen::width, Screen::height, 0);

	this->outline->originBuffer = new FrameBuffer(Screen::width,Screen::height);
	this->outline->originBuffer->Initialize();

	// this->outline->blendBuffer = FrameBuffer::GenSingleHDRColorFramebuffer(Screen::width, Screen::height, 0);

	this->outline->blendBuffer = new FrameBuffer(Screen::width, Screen::height);
	this->outline->blendBuffer->Initialize();

	// this->outline->outputBuffer = FrameBuffer::GenSingleHDRColorFramebuffer(Screen::width, Screen::height, 0);
	this->outline->outputBuffer = new FrameBuffer(Screen::width,Screen::height);
	this->outline->outputBuffer->Initialize();
}

void PostProcessing::Initialize() 
{ 
	if (this->enabled == false)
		return;
	// outputFramebuffer = FrameBuffer::GenColorFramebuffer(Screen::width, Screen::height, 0);
	outputFramebuffer = new FrameBuffer(Screen::width,Screen::height);
	outputFramebuffer->colorFormat = ColorFormat::RGB24;
	outputFramebuffer->Initialize();

	outputMaterial = new Material(Shader::Load("fullscreen/fullscreen.vs", "fullscreen/fullscreen.fs"));
	
	this->fsRenderer = new FullScreenRenderer();
	this->fsRenderer->name = "(FSR)PostProcessing";
	this->fsRenderer->Init();

	// if (this->antiAliasing->enabled)
	// {
	// 	this->srcFramebuffer = FrameBuffer::GenMSColorFramebuffer(Screen::width, Screen::height, this->antiAliasing->samples);
	// }

	if (this->bloom->enable)
	{
		this->bloom->material = new Material(Shader::Load("fullscreen/fullscreen.vs", "postprocessing/bloom/bloom.fs"));
		this->bloom->gaussianBlurMaterial = new Material(Shader::Load("fullscreen/fullscreen.vs","postprocessing/bloom/gaussianblur.fs"));
		this->bloom->bloomAddMaterial = new Material(Shader::Load("fullscreen/fullscreen.vs","postprocessing/bloom/bloomadd.fs"));
		this->bloom->material->shader->enableLighting = false;
		this->bloom->buffer = FrameBuffer::GenHDRColorFramebuffer(Screen::width, Screen::height, 0, 2);
		// this->bloom->bloomBuffer = FrameBuffer::GenSingleHDRColorFramebuffer(Screen::width,Screen::height,0);
		// this->bloom->bloomTemp = FrameBuffer::GenSingleHDRColorFramebuffer(Screen::width, Screen::height, 0);

		this->bloom->bloomBuffer = new FrameBuffer(Screen::width,Screen::height);
		this->bloom->bloomBuffer->colorFormat = ColorFormat::RGB16Float;
		this->bloom->bloomBuffer->Initialize();

		this->bloom->bloomTemp = new FrameBuffer(Screen::width,Screen::height);
		this->bloom->bloomTemp->colorFormat = ColorFormat::RGB16Float;
		this->bloom->bloomTemp->Initialize();
	}

	if (this->toneMapping->enable) 
	{
		this->toneMapping->material = new Material(Shader::Load("fullscreen/fullscreen.vs","postprocessing/tonemapping/tonemapping.fs"));
		this->toneMapping->material->shader->enableLighting = false;
		// this->toneMapping->buffer = FrameBuffer::GenColorFramebuffer(Screen::width, Screen::height, 0);
		this->toneMapping->buffer = new FrameBuffer(Screen::width,Screen::height);
		this->toneMapping->buffer->colorFormat = ColorFormat::RGB24;
		this->toneMapping->buffer->Initialize();
	}

	// this->srcFramebuffer = FrameBuffer::GenSingleHDRColorFramebuffer(Screen::width, Screen::height, 0);
	// this->dstFramebuffer = FrameBuffer::GenSingleHDRColorFramebuffer(Screen::width, Screen::height, 0);
	this->srcFramebuffer = new FrameBuffer(Screen::width,Screen::height);
	this->srcFramebuffer->colorFormat = ColorFormat::RGBA16Float;
	this->srcFramebuffer->depthbuffer = FrameBuffer::OnlyDepth;
	this->srcFramebuffer->Initialize();

	this->dstFramebuffer = new FrameBuffer(Screen::width,Screen::height);
	this->dstFramebuffer->colorFormat = ColorFormat::RGB16Float;
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
				this->Blit(hSample ? this->bloom->bloomTemp : this->bloom->bloomBuffer, hSample ? this->bloom->bloomBuffer : this->bloom->bloomTemp, this->bloom->gaussianBlurMaterial);
			firstTransfer = false;
			transfer = this->bloom->bloomTemp;
		 	hSample = !hSample;
		}

		this->bloom->bloomAddMaterial->shader->setTexture("BrightTexture",transfer->buffer);
		this->Blit(this->bloom->buffer, this->bloom->bloomBuffer, this->bloom->bloomAddMaterial, 0);
		transfer = this->bloom->bloomBuffer;
		// blend src and bright area
	}

	// outline
	if (this->outline->enable)
	{
		this->outline->outlineBlendMaterial->shader->setTexture("outlineTexture", this->outline->buffer->buffer);
		this->Blit(this->outline->originBuffer, this->outline->blendBuffer, this->outline->outlineBlendMaterial);

		this->outline->outputMateiral->shader->setTexture("addTexture", this->outline->blendBuffer->buffer);
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
}

void PostProcessing::Blit(FrameBuffer* src,FrameBuffer* dst)
{
	glBindFramebuffer(GL_READ_FRAMEBUFFER, src->framebufferId);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, dst->framebufferId);
	glBlitFramebuffer(0, 0, src->width, src->height, 0, 0, dst->width, dst->height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void PostProcessing::Blit(FrameBuffer* src, FrameBuffer* dst, Material* material) 
{
	this->fsRenderer->material = material;
	this->fsRenderer->material->shader->setTexture(MAIN_TEX, src->buffer);// 这里根据是否运行使用MTR取不同的buffer attachment

	Camera::current = Camera::main;
	Camera::current->framebuffer = dst;
	Camera::current->framebuffer->Bind();
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glClearColor(0.1f,0.4f,0.7f,1.0f);
	unsigned int* postProcessingLayer = new unsigned int[1]{ Layer::PostProcessing };
	Renderable::Draw(1, postProcessingLayer);
	Camera::current->framebuffer->Unbind();
	delete[] postProcessingLayer;
}

void PostProcessing::Blit(FrameBuffer* src, FrameBuffer* dst, Material* material,unsigned int attachment)
{
	this->fsRenderer->material = material;
	this->fsRenderer->material->shader->setTexture(MAIN_TEX, src->buffers[attachment]);// 这里根据是否运行使用MTR取不同的buffer attachment

	Camera::current = Camera::main;
	Camera::current->framebuffer = dst;
	Camera::current->framebuffer->Bind();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	unsigned int* postProcessingLayer = new unsigned int[1]{ Layer::PostProcessing };
	Renderable::Draw(1, postProcessingLayer);
	Camera::current->framebuffer->Unbind();
	delete[] postProcessingLayer;
}