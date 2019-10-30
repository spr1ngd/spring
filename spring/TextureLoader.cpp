#include "textureLoader.h"
#include "soil.h"
#include "texture.h"

#pragma comment(lib,"soil.lib")

using namespace std;
using namespace spring;

std::map<const char*, Texture*> TextureLoader::textures;

TextureLoader::TextureLoader() 
{

}

bool TextureLoader::IsExist(const char* filePath, Texture* texture) 
{
	texture = textures[filePath];
	return texture != nullptr;
}

void TextureLoader::Caching(const char* filePath, Texture* texture) 
{
	auto cache = textures.find(filePath);
	if (cache != textures.end())
		return;
	textures.insert(std::pair<const char*, Texture*>(filePath, texture));
}

Texture* TextureLoader::GenPureWhiteTexture()
{
	const char* textureName = "__spring__engine__pure__white__texture__";
	Texture* texture = nullptr;
	if (!IsExist(textureName, texture)) 
	{
		texture = new Texture();
		texture->textureName = textureName;
		texture->textureType = "pure color";
		GLuint tex;
		glGenTextures(1, &tex);
		glBindTexture(GL_TEXTURE_2D, tex);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		unsigned char* data = new unsigned char[4]{ 255,255,255,255 };
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		delete[] data;
		texture->textureId = tex;
		Caching(textureName, texture);
	}
	return texture;
}

Texture* TextureLoader::Load(const char* filePath) 
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
	Texture* texture = new Texture();
	texture->textureName = filePath;
	texture->textureId = textureId;
	Caching(filePath, texture);
	return texture;
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