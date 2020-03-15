#include "GL/glew.h"
#include "renderbuffer.h"

using namespace spring;

RenderBuffer::RenderBuffer(unsigned int width, unsigned int height, RenderBufferFormat format) : width(256), height(256), format(RenderBufferFormat::DepthWithStencil)
{
	this->width = width;
	this->height = height;
	this->format = format;
}

void RenderBuffer::Initialize()
{
	unsigned int internalFormat = this->getFormat();
	unsigned int attachment = this->getAttachment();

	glGenRenderbuffers(1, &this->buffer);
	glBindRenderbuffer(GL_RENDERBUFFER, this->buffer);
	if (this->multiSampleLevel == 0) glRenderbufferStorage(GL_RENDERBUFFER, internalFormat, this->width, this->height);
	else glRenderbufferStorageMultisample(GL_RENDERBUFFER, this->multiSampleLevel, internalFormat, this->width, this->height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, attachment, GL_RENDERBUFFER, this->buffer);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

void RenderBuffer::Release() 
{
	glDeleteRenderbuffers(1, &this->buffer);
}

unsigned int RenderBuffer::getFormat()
{
	switch (this->format)
	{
	case RenderBufferFormat::Depth:
		return GL_DEPTH_COMPONENT24;
	case RenderBufferFormat::Stencil:
		return GL_STENCIL_COMPONENTS;
	case RenderBufferFormat::DepthWithStencil:
		return GL_DEPTH24_STENCIL8;
	default:
		break;
	}
}
unsigned int RenderBuffer::getAttachment()
{
	switch (this->format)
	{
	case RenderBufferFormat::Depth:
		return GL_DEPTH_ATTACHMENT;
	case RenderBufferFormat::Stencil:
		return GL_STENCIL_ATTACHMENT;
	case RenderBufferFormat::DepthWithStencil:
		return GL_DEPTH_STENCIL_ATTACHMENT;
	default:
		break;
	}
}