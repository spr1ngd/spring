#include "uniformbuffer.h"
#include "glew.h"
#include "glm/glm.hpp"

using namespace spring;

UniformBuffer::UniformBuffer(unsigned int size,unsigned int drawMode)
{
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_UNIFORM_BUFFER, buffer);
	glBufferData(GL_UNIFORM_BUFFER, size, NULL, drawMode);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	glBindBufferRange(GL_UNIFORM_BUFFER, 0, buffer, 0, size);
}

void UniformBuffer::BindSubData(unsigned int offset, unsigned int size ,const void* data) 
{
	glBindBuffer(GL_UNIFORM_BUFFER,this->buffer);
	glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
	glBindBuffer(GL_UNIFORM_BUFFER,0);
}

void UniformBuffer::BlockBinding(const unsigned int gpuProgram, const char* blockName, const unsigned int bindingPoint)
{
	unsigned int blockIndex = glGetUniformBlockIndex(gpuProgram, blockName);
	glUniformBlockBinding(gpuProgram, blockIndex, bindingPoint);
}