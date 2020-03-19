#include "framebuffer.h"
#include "console.h"

using namespace spring;

std::vector<FrameBuffer*> FrameBuffer::framebuffers;

FrameBuffer::FrameBuffer(unsigned int width, unsigned int height , ColorFormat colorFormat ,unsigned int bufferSize)
{
	this->width = width;
	this->height = height;
	this->colorFormat = colorFormat;
	this->buffersSize = bufferSize;
}

void FrameBuffer::Initialize()
{
	glGenFramebuffers(1, &framebufferId);
	glBindFramebuffer(GL_FRAMEBUFFER, framebufferId);
	unsigned int multiSampleLevel = this->getMultiSampleLevel();

	for (unsigned int i = 0; i < this->buffersSize; i++) 
	{
		Texture* tex = new Texture(width, height);
		tex->wrap = this->wrap;
		tex->filter = this->filter;
		tex->format = this->colorFormat;
		tex->generateMipMap = this->generateMipMap;
		tex->mipmapLevel = this->mipmapLevel;
		tex->multiSampleLevel = multiSampleLevel;
		tex->Initialize();
		if (this->colorFormat == ColorFormat::Shadow) 
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_COMPONENT , tex->textureTarget, tex->textureId, mipmapLevel);
		else 
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, tex->textureTarget, tex->textureId, mipmapLevel);
		this->textures.push_back(tex);
	}

	GLuint* attachments = new GLuint[this->buffersSize];
	for (unsigned int i = 0; i < buffersSize; i++)
		attachments[i] = GL_COLOR_ATTACHMENT0 + i;
	glDrawBuffers(buffersSize, attachments);
	delete[] attachments;

	if (this->depthbuffer != DepthBuffer::NoneDepth)
	{
		auto renderBufferFormat = getRenderBufferFormat();
		this->renderbuffer = new RenderBuffer(width, height, renderBufferFormat);
		this->renderbuffer->multiSampleLevel = multiSampleLevel;
		this->renderbuffer->Initialize();
		this->rbo = this->renderbuffer->buffer;
	}

	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (status != GL_FRAMEBUFFER_COMPLETE)
	{
		PRINT_ERROR("[spring engine] : generate frame buffer object error : (0x%x)", status);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		for (auto item = textures.begin(); item != textures.end(); item++)
		{
			Texture* tex = *item;
			tex->Release();
			delete tex;
		}
		delete renderbuffer;
		return;
	}
	this->textures = textures;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	this->framebuffers.push_back(this);
}
void FrameBuffer::Release()
{
	for (auto item = this->framebuffers.begin(); item != this->framebuffers.end(); item++)
	{
		FrameBuffer* fbo = *item;
		if (fbo->framebufferId == this->framebufferId)
		{
			this->framebuffers.erase(item);
			break;
		}
	}
	for (auto item = textures.begin(); item != textures.end(); item++)
	{
		Texture* tex = *item;
		tex->Release();
		delete tex;
	}
	if (nullptr != this->renderbuffer)
	{
		this->renderbuffer->Release();
		delete this->renderbuffer;
	}
	glDeleteFramebuffers(1, &this->framebufferId);
}

void FrameBuffer::Bind() 
{
	glBindFramebuffer(GL_FRAMEBUFFER, this->framebufferId);
}
void FrameBuffer::Unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
} 

void FrameBuffer::BindRenderbuffer() 
{
	glBindFramebuffer(GL_RENDERBUFFER,this->rbo);
}
void FrameBuffer::CaptureMipmap(unsigned int level) 
{
	glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->GetBuffer(), level);
}
void FrameBuffer::CubemapCapture(unsigned int cubemapId ,unsigned int index, unsigned int level)
{
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,GL_TEXTURE_CUBE_MAP_POSITIVE_X + index,cubemapId, level);
}
unsigned int FrameBuffer::GetBuffer(unsigned int index) 
{
	return this->textures[index]->textureId;
}
Colorf FrameBuffer::ReadPixel(unsigned int x, unsigned int y) 
{
	glBindFramebuffer(GL_READ_FRAMEBUFFER, this->framebufferId);
	float rgb[3];
	glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, rgb);
	glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
	return Colorf(rgb[0], rgb[1], rgb[2], 1.0f);
}

RenderBuffer::RenderBufferFormat FrameBuffer::getRenderBufferFormat()
{
	switch (this->depthbuffer)
	{
	case DepthBuffer::OnlyDepth:
		return RenderBuffer::Depth;
	case DepthBuffer::OnlyStencil:
		return RenderBuffer::Stencil;
	case DepthBuffer::DepthWithStencil:
		return RenderBuffer::DepthWithStencil;
	default:
		return RenderBuffer::RenderBufferFormat::DepthWithStencil;
	}
}
unsigned int FrameBuffer::getMultiSampleLevel()
{
	switch (this->antiAliasing)
	{
	case AntiAliasingLevel::Level0:
		return 0;
	case AntiAliasingLevel::Level2:
		return 2;
	case AntiAliasingLevel::Level4:
		return 4;
	case AntiAliasingLevel::Level8:
		return 8;
	case AntiAliasingLevel::Level16:
		return 16;
	default:
		return 0;
	}
}

void FrameBuffer::Blit(FrameBuffer& dst) 
{
	glBindFramebuffer(GL_READ_FRAMEBUFFER, this->framebufferId);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, dst.framebufferId);
	glBlitFramebuffer(0, 0, this->width, this->height, 0, 0, dst.width, dst.height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}