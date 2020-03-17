#include "texture.h"

using namespace spring;

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
	else // load from memory cache
	{
		// this->textureId = texture->textureId;
		// this->textureName = texture->textureName;
		// this->textureType = texture->textureType;
	}
}

void Texture::Initialize()
{
	unsigned int wrapMode = this->getWrapMode();
	unsigned int filterMode = this->getFilterMode();
	unsigned int internalFormat = this->getInternalFormat();
	unsigned int outputFormat = this->getOutputFormat();
	unsigned int dataType = this->getDataType();
	unsigned int mipmapLevel = (this->generateMipMap == true) ? this->mipmapLevel : 0;
	glGenTextures(1, &this->textureId);

	if (this->multiSampleLevel == 0)
	{
		this->textureTarget = GL_TEXTURE_2D;
		glBindTexture(GL_TEXTURE_2D, this->textureId);
		glTexImage2D(GL_TEXTURE_2D, mipmapLevel, internalFormat, this->width, this->height, 0, outputFormat, dataType, NULL);
		if (this->generateMipMap)
			glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterMode);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterMode);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, wrapMode);

		if (this->format == ColorFormat::Shadow)
		{
			float* border = new float[4]{1.0f,1.0f,1.0f,1.0f};
			glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, border);
		}
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else 
	{
		this->textureTarget = GL_TEXTURE_2D_MULTISAMPLE;
		glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, this->textureId);
		glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, this->multiSampleLevel, internalFormat, this->width, this->height, GL_TRUE);
		if (this->generateMipMap)
			glGenerateMipmap(GL_TEXTURE_2D_MULTISAMPLE);
		//glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_MIN_FILTER, filterMode);
		//glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_MAG_FILTER, filterMode);
		//glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_WRAP_T, wrapMode);
		//glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_WRAP_S, wrapMode);
		//glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_WRAP_R, wrapMode);
		glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);
	}
}

void Texture::Release()
{

}

Colorf Texture::ReadPixel(unsigned int x,unsigned int y) 
{
	glBindTexture(GL_TEXTURE_2D, this->textureId);
	glCopyTexImage2D(GL_TEXTURE_2D, 0, this->getOutputFormat(), x, y, this->width, this->height, 0);
	float rgba[4];
	glGetTexImage(GL_TEXTURE_2D, 0, this->getOutputFormat(), this->getDataType(), &rgba);
	return Colorf(rgba[0], rgba[1], rgba[2], rgba[3]);
}

unsigned int Texture::getWrapMode()
{
	switch (this->wrap)
	{
	case spring::WrapMode::Repeat:
		return GL_REPEAT;
	case spring::WrapMode::ClampToEdge:
		return GL_CLAMP_TO_EDGE;// GL_CLAMP_TO_EDGE_EXT/SGIS
	case spring::WrapMode::ClampToBorder:
		return GL_CLAMP_TO_BORDER;
	case spring::WrapMode::MirrorRepeat:
		return GL_MIRRORED_REPEAT;
	default:
		return GL_REPEAT;
	}
}
unsigned int Texture::getFilterMode()
{
	switch (this->filter)
	{
	case spring::FilterMode::Linear:
		return GL_LINEAR;
	case spring::FilterMode::Nearest:
		return GL_NEAREST;;
	case spring::FilterMode::Linear_MipMapLinear:
		return GL_LINEAR_MIPMAP_LINEAR;
	case spring::FilterMode::Linear_MinpMapNearest:
		return GL_LINEAR_MIPMAP_NEAREST;
	case spring::FilterMode::Nearest_MipMapLinear:
		return GL_NEAREST_MIPMAP_LINEAR;
	case spring::FilterMode::Nearest_MipMapNearest:
		return GL_NEAREST_MIPMAP_NEAREST;
	default:
		return GL_NEAREST;
	}
}
unsigned int Texture::getInternalFormat() 
{
	switch (this->format)
	{
	case spring::ColorFormat::R8:
		return GL_R;
	case spring::ColorFormat::RG16:
		return GL_RG;
	case spring::ColorFormat::RGB24:
		return GL_RGB;
	case spring::ColorFormat::RGB16Float:
		return GL_RGB16F;
	case spring::ColorFormat::RGB32Float:
		return GL_RGB32F;
	case spring::ColorFormat::RGBA32:
		return GL_RGBA;
	case spring::ColorFormat::RGBA16Float:
		return GL_RGBA16F;
	case spring::ColorFormat::RGBA32Float:
		return GL_RGBA32F;
	case spring::ColorFormat::Shadow:
		return GL_DEPTH_COMPONENT;
	default:
		return GL_RGBA;
	}
}
unsigned int Texture::getOutputFormat()
{
	switch (this->format)
	{
	case spring::ColorFormat::R8:
		return GL_R;
	case spring::ColorFormat::RG16:
		return GL_RG;
	case spring::ColorFormat::RGB24:
		return GL_RGB;
	case spring::ColorFormat::RGB16Float:
		return GL_RGB;
	case spring::ColorFormat::RGB32Float:
		return GL_RGB;
	case spring::ColorFormat::RGBA32:
		return GL_RGBA;
	case spring::ColorFormat::RGBA16Float:
		return GL_RGBA;
	case spring::ColorFormat::RGBA32Float:
		return GL_RGBA;
	case spring::ColorFormat::Shadow:
		return GL_DEPTH_COMPONENT;
	default:
		return GL_RGBA;
	}
}
unsigned int Texture::getDataType()
{
	switch (this->format)
	{
	case spring::ColorFormat::R8:
		return GL_UNSIGNED_BYTE;
	case spring::ColorFormat::RG16:
		return GL_UNSIGNED_BYTE;
	case spring::ColorFormat::RGB24:
		return GL_UNSIGNED_BYTE;
	case spring::ColorFormat::RGBA32:
		return GL_UNSIGNED_BYTE;
	case spring::ColorFormat::RGBA32Float:
		return GL_FLOAT;
	case spring::ColorFormat::Shadow:
		return GL_FLOAT;
	default:
		return GL_UNSIGNED_BYTE;
	}
}