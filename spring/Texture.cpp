#include "Texture.h"

using namespace spring;

Texture::Texture()
{

}

Texture::Texture(const char* filePath) 
{
	this->Load(filePath);
}

void Texture::Load(const char* filePath) 
{
	Texture* texture = nullptr;
	if (!TextureLoader::IsExist(filePath, texture))
	{
		auto loader = TextureLoader();
		auto texture = loader.Load(filePath);
		this->textureId = texture->textureId;
		TextureLoader::Caching(filePath, this);
	}
	else
	{
		this->textureId = texture->textureId;
		this->textureName = texture->textureName;
		this->textureType = texture->textureType;
	}
}

void Texture::Release() 
{
	
}