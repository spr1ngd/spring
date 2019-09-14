#include "textureLoader.h"
#include "soil.h"

#pragma comment(lib,"soil.lib")

using namespace std;
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

GLuint TextureLoader::LoadCubemap(const std::string filePaths) 
{
	const string front = "/front.png\0";
	const string back = "/back.png\0";
	const string left = "/left.png\0";
	const string right = "/right.png\0";
	const string top = "/top.png\0";
	const string bottom = "/bottom.png\0";
	GLuint cubemap = TextureLoader::LoadCubemap(
		(filePaths + right).c_str(),
		(filePaths + left).c_str(),
		(filePaths + top).c_str(),
		(filePaths + bottom).c_str(),
		(filePaths + back).c_str(),
		(filePaths + front).c_str());
	return cubemap;
}

GLuint TextureLoader::LoadCubemap(const char* right, const char* left, const char* top, const char* bottom, const char* back, const char* front)
{
	GLuint cubemap = SOIL_load_OGL_cubemap(right, left, top, bottom, back, front, 0, 0, SOIL_FLAG_POWER_OF_TWO);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	return cubemap;
}