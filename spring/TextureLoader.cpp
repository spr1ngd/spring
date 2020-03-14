#include "textureLoader.h"
#include "SOIL/soil.h"
#include "texture.h"
#include "screen.h"
#include "console.h"

using namespace std;
using namespace spring;

std::map<const char*, Texture*> TextureLoader::textures;
std::vector<Cubemap*> TextureLoader::cubemaps;

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

void TextureLoader::Release() 
{
	if (textures.size() <= 0)
		return;
	for (auto kv : textures)
		(&kv)->second->Release();
}

Texture* TextureLoader::CreateTexture(unsigned int width, unsigned int height, unsigned int level )
{
	Texture* result = new Texture();
	result->width = width;
	result->height = height;
	result->mipmapLevel = level;

	unsigned int textureId;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D,textureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	auto pixelCount = result->width* result->height * 4;
	unsigned int* data = new unsigned int[pixelCount];
	glTexImage2D(GL_TEXTURE_2D, result->mipmapLevel, GL_RGBA, result->width, result->height, 0, GL_RGBA, GL_FLOAT, data);
	delete[] data;
	result->textureId = textureId;
	// TODO: replaced by GUID
	char name[32];
	sprintf_s(name, "__spring_engine__%d__teture__", textureId);
	Caching(name,result);
	return result;
}

Texture* TextureLoader::CreatePureWhiteTexture()
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
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		delete[] data;
		texture->textureId = tex;
		Caching(textureName, texture);
	}
	return texture;
}

Texture* TextureLoader::Load(const char* filePath ,bool invertY)
{
	unsigned int flags = SOIL_FLAG_POWER_OF_TWO;
	if (invertY)
		flags |= SOIL_FLAG_INVERT_Y;
	GLuint textureId = SOIL_load_OGL_texture(filePath,0,0,flags);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	Texture* texture = new Texture();
	texture->textureName = filePath;
	texture->textureId = textureId;
	Caching(filePath, texture);
	return texture;
}

void TextureLoader::SaveToBMP(const char* filepath) 
{
	auto pixelCount = Screen::width * Screen::height * 4;
	unsigned char* pixels = new unsigned char[pixelCount];
	glReadPixels(0, 0, Screen::width, Screen::height, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
	TextureLoader::SaveToBMP(filepath, Screen::width, Screen::height, pixels);
	delete[] pixels;
}

void TextureLoader::SaveToBMP(const char* filePath, int width, int height, const unsigned char* pixels)
{
	int result = SOIL_save_image(filePath, SOIL_SAVE_TYPE_BMP, width, height, 4, pixels);
	if (result == 0)
		PRINT_ERROR("save image failed.");
}

#pragma region cubemap

Cubemap* TextureLoader::CreateCubemap(unsigned int width, unsigned int height)
{
	Cubemap* cubemap = new Cubemap();
	cubemap->level = 0;
	cubemap->width = width;
	cubemap->height = height;
	unsigned int cubemapId;
	glGenTextures(1, &cubemapId);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapId);
	for (unsigned int i = 0; i < 6; i++) 
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, cubemap->level, GL_RGB16F, cubemap->width, cubemap->height, 0, GL_RGB, GL_FLOAT, nullptr);
	glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_R,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	cubemap->cubemap = cubemapId;
	cubemaps.push_back(cubemap);
	return cubemap;
}

Cubemap* TextureLoader::CreateCubemapMipmap(unsigned int width, unsigned int height) 
{
	Cubemap* result = new Cubemap();
	result->level = 0;
	result->width = width;
	result->height = height;
	unsigned int cubemapId;
	glGenTextures(1, &cubemapId);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapId);
	for (unsigned int i = 0; i < 6; i++)
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, result->level, GL_RGB16F, result->width, result->height, 0, GL_RGB, GL_FLOAT, nullptr);
	glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_R,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

	result->cubemap = cubemapId;
	cubemaps.push_back(result);
	return result;
}

Cubemap* TextureLoader::LoadCubemap(const std::string filePaths) 
{
	const string extension = ".png\0";
	const string front = "/front" + extension;
	const string back = "/back" + extension;
	const string left = "/left" + extension;
	const string right = "/right" + extension;
	const string top = "/top" + extension;
	const string bottom = "/bottom" + extension;
	return TextureLoader::LoadCubemap(
		(filePaths + right).c_str(),
		(filePaths + left).c_str(),
		(filePaths + top).c_str(),
		(filePaths + bottom).c_str(),
		(filePaths + back).c_str(),
		(filePaths + front).c_str());
}

Cubemap* TextureLoader::LoadCubemap(const char* right, const char* left, const char* top, const char* bottom, const char* back, const char* front)
{
	GLuint cubemap = SOIL_load_OGL_cubemap(right, left, top, bottom, back, front, 0, 0, SOIL_FLAG_POWER_OF_TWO);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	Cubemap* result = new Cubemap();
	result->cubemap = cubemap;
	cubemaps.push_back(result);
	return result;
}

#pragma endregion