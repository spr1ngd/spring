#include "framebufferobject.h"
#include "console.h"

using namespace spring;

std::vector<FrameBufferObject*> FrameBufferObject::framebuffers;

FrameBufferObject::FrameBufferObject(int width,int height,GLenum attachment,int level)
{
	this->width = width;
	this->height = height;
	this->attachment = attachment;
	this->level = level;
}

void FrameBufferObject::Bind() 
{
	glBindFramebuffer(GL_FRAMEBUFFER, this->bufferId);
}

void FrameBufferObject::Unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBufferObject::Delete() 
{
	glDeleteFramebuffers(1, &this->bufferId);
}

FrameBufferObject* FrameBufferObject::GenColorFramebuffer(int width, int height, int level) 
{
	FrameBufferObject* fbo = new FrameBufferObject(width, height, GL_COLOR_ATTACHMENT0, level);
	unsigned int framebuffer;
	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	unsigned int colorbuffer;
	glGenTextures(1, &colorbuffer);
	glBindTexture(GL_TEXTURE_2D, colorbuffer);
	glTexImage2D(GL_TEXTURE_2D, fbo->level, GL_RGBA, fbo->width, fbo->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, fbo->attachment, GL_TEXTURE_2D, colorbuffer, fbo->level);
	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (status != GL_FRAMEBUFFER_COMPLETE)
	{
		Console::ErrorFormat("[spring engine] : generate color buffer object error : (0x%x)", status);
		return nullptr;
	}
	fbo->bufferId = framebuffer;
	fbo->colorbuffer = colorbuffer;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	framebuffers.push_back(fbo);
	return fbo;
}

FrameBufferObject* FrameBufferObject::GenDepthFramebuffer(int width, int height) 
{
	return nullptr;
}

FrameBufferObject* FrameBufferObject::GenStencilFramebuffer(int width, int height) 
{
	return nullptr;
}