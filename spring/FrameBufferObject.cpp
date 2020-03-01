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
	glBindFramebuffer(GL_FRAMEBUFFER, this->framebufferId);
}

void FrameBufferObject::BindRenderbuffer() 
{
	glBindFramebuffer(GL_RENDERBUFFER,this->rbo);
}

void FrameBufferObject::CaptureMipmap(unsigned int level/* =0 */) 
{
	glFramebufferTexture2D(GL_FRAMEBUFFER,this->attachment, GL_TEXTURE_2D, this->buffer, level);
}

void FrameBufferObject::CubemapCapture(unsigned int cubemapId ,unsigned int index, unsigned int level)
{
	glFramebufferTexture2D(GL_FRAMEBUFFER,this->attachment,GL_TEXTURE_CUBE_MAP_POSITIVE_X + index,cubemapId, level);
}

void FrameBufferObject::Unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBufferObject::Delete() 
{
	for (auto item = this->framebuffers.begin(); item != this->framebuffers.end(); item++)
	{
		FrameBufferObject* fbo = *item;
		if (fbo->framebufferId == this->framebufferId)
		{
			this->framebuffers.erase(item);
			break;
		}
	}
	glDeleteFramebuffers(1, &this->framebufferId);
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
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, fbo->attachment, GL_TEXTURE_2D, colorbuffer, fbo->level);
	glBindTexture(GL_TEXTURE_2D, 0);

	unsigned int rbo;
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, fbo->width, fbo->height); // use a single renderbuffer object for both a depth AND stencil buffer.
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo); // now actually attach it

	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (status != GL_FRAMEBUFFER_COMPLETE)
	{
		Console::ErrorFormat("[spring engine] : generate color buffer object error : (0x%x)", status);
		return nullptr;
	}

	fbo->framebufferId = framebuffer;
	fbo->buffer = colorbuffer;
	fbo->rbo = rbo;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	framebuffers.push_back(fbo);
	return fbo;
}

FrameBufferObject* FrameBufferObject::GenMSColorFramebuffer( int width, int height, int samples)
{
	FrameBufferObject* fbo = new FrameBufferObject(width, height, GL_COLOR_ATTACHMENT0, 0);
	fbo->enableMS = true;
	unsigned int framebuffer;
	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

	unsigned int colorbuffer;
	glGenTextures(1, &colorbuffer);
	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, colorbuffer);
	glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, GL_RGB, fbo->width, fbo->height, GL_TRUE);
	glFramebufferTexture2D(GL_FRAMEBUFFER, fbo->attachment, GL_TEXTURE_2D_MULTISAMPLE, colorbuffer, fbo->level);
	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);

	unsigned int renderbuffer;
	glGenRenderbuffers(1, &renderbuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, renderbuffer);
	glRenderbufferStorageMultisample(GL_RENDERBUFFER, samples, GL_DEPTH24_STENCIL8, fbo->width, fbo->height);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderbuffer);

	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (status != GL_FRAMEBUFFER_COMPLETE) 
	{
		Console::ErrorFormat("[spring engine] : generate multi sample color buffer object error : (0x%x)", status);
		return nullptr;
	}
	fbo->framebufferId = framebuffer;
	fbo->buffer = colorbuffer;
	fbo->rbo = renderbuffer;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	framebuffers.push_back(fbo);
	return fbo;
}

FrameBufferObject* FrameBufferObject::GenSingleHDRColorFramebuffer(int width, int height, int level)
{
	FrameBufferObject* fbo = new FrameBufferObject(width, height, GL_COLOR_ATTACHMENT0, level);
	fbo->enableHDR;
	unsigned int framebuffer;
	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

	unsigned int colorbuffer;
	glGenTextures(1, &colorbuffer);
	glBindTexture(GL_TEXTURE_2D, colorbuffer);
	glTexImage2D(GL_TEXTURE_2D, fbo->level, GL_RGB16F, fbo->width, fbo->height, 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorbuffer, fbo->level);
	glBindTexture(GL_TEXTURE_2D, 0);

	unsigned int renderbuffer;
	glGenRenderbuffers(1, &renderbuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, renderbuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, fbo->width, fbo->height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderbuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (status != GL_FRAMEBUFFER_COMPLETE)
	{
		Console::ErrorFormat("[spring engine] : generate hdr color buffer object error : (0x%x)", status);
		return nullptr;
	}
	fbo->framebufferId = framebuffer;
	fbo->buffer = colorbuffer;
	fbo->rbo = renderbuffer;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	framebuffers.push_back(fbo);
	return fbo;
}


FrameBufferObject* FrameBufferObject::GenHDRColorFramebuffer(int width, int height, int level, unsigned int size)
{
	FrameBufferObject* fbo = new FrameBufferObject(width, height, GL_COLOR_ATTACHMENT0, level);
	fbo->enableHDR = true;
	fbo->enableMRT = true;
	unsigned int framebuffer;
	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

	unsigned int* textures = new unsigned int[size];
	glGenTextures(size, textures);
	for (unsigned int i = 0; i < size; i++) 
	{
		glBindTexture(GL_TEXTURE_2D, textures[i]);
		glTexImage2D(GL_TEXTURE_2D, fbo->level, GL_RGB16F, fbo->width, fbo->height, 0, GL_RGBA, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, textures[i], fbo->level);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	unsigned int renderbuffer;
	glGenRenderbuffers(1, &renderbuffer);
	glBindRenderbuffer(GL_RENDERBUFFER,renderbuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, fbo->width, fbo->height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderbuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (status != GL_FRAMEBUFFER_COMPLETE) 
	{
		Console::ErrorFormat("[spring engine] : generate hdr color buffer object error : (0x%x)", status);
		return nullptr;
	}
	fbo->framebufferId = framebuffer;
	fbo->buffers = textures;
	fbo->rbo = renderbuffer;
	GLuint* attachments = new GLuint[size];
	for (unsigned int i = 0; i < size; i++)
		attachments[i] = GL_COLOR_ATTACHMENT0 + i;
	glDrawBuffers(size, attachments);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	framebuffers.push_back(fbo);
	// delete[] textures;
	delete[] attachments;
	return fbo;
}

FrameBufferObject* FrameBufferObject::GenDepthFramebuffer(int width, int height) 
{
	FrameBufferObject* fbo = new FrameBufferObject(width, height,GL_DEPTH_ATTACHMENT,0);
	GLuint framebuffer;
	glGenFramebuffers(1, &framebuffer);
	// - Create depth texture
	GLuint depthbuffer;
	glGenTextures(1, &depthbuffer);
	glBindTexture(GL_TEXTURE_2D, depthbuffer);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, fbo->width, fbo->height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	float* buffer = new float[4]{ 1.0f,1.0f ,1.0,1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, buffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthbuffer, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	delete[] buffer;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (status != GL_FRAMEBUFFER_COMPLETE)
	{
		Console::ErrorFormat("[spring engine] : generate depth buffer object error : (0x%x)", status);
		return nullptr;
	}
	fbo->framebufferId = framebuffer;
	fbo->buffer = depthbuffer;
	framebuffers.push_back(fbo);
	return fbo;
}

FrameBufferObject* FrameBufferObject::GenStencilFramebuffer(int width, int height) 
{
	return nullptr;
}