#include "TextureLoader.h"
#include "soil.h"

#pragma comment(lib,"soil.lib")

using namespace spring;

TextureLoader::TextureLoader() 
{

}

GLuint TextureLoader::Load(const char* filePath) 
{
	this->filePath = filePath;
	unsigned int flags = SOIL_FLAG_POWER_OF_TWO;
	GLuint textureId = SOIL_load_OGL_texture(filePath,0,0,flags);
	// todo: flag invert y
	// todo: wrap mode GL_CLAMP_TO_EDGE
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_2D, 0);
	return textureId;
}