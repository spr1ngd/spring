#pragma once
#include "GL/glew.h"
#include "textureloader.h"
#include "colorf.h"

namespace spring 
{
	enum WrapMode 
	{
		Repeat,
		ClampToEdge,
		ClampToBorder,
		MirrorRepeat
	};

	enum FilterMode 
	{
		Linear,
		Nearest,
		Linear_MipMapLinear,
		Linear_MinpMapNearest,
		Nearest_MipMapLinear,
		Nearest_MipMapNearest
	};

	enum ColorFormat 
	{
		R8,
		RG16,
		RGB24,
		RGBA32,
		RGBAFloat,
	};

	enum AntiAliasingLevel
	{
		Level0,
		Level2,
		Level4,
		Level8,
		Level16
	};

	class Texture 
	{
	public:
		const char* textureName = "";
		const char* textureType = "";
		unsigned int textureTarget = -1;
		unsigned int textureId = -1;
		unsigned int width = 256;
		unsigned int height = 256;
		WrapMode wrap = WrapMode::Repeat;
		FilterMode filter = FilterMode::Linear;
		ColorFormat format = ColorFormat::RGBA32;
		bool generateMipMap = false;
		unsigned int mipmapLevel = 0;
		unsigned int multiSampleLevel = 0;

		Texture() {}
		Texture(unsigned int width, unsigned int height):width(256),height(256)
		{
			this->width = width;
			this->height = height;
		}
		Texture(const char* filePath);
		void Load(const char* filePath);
		void Release();
		void Initialize();
		
		Colorf ReadPixel(unsigned int x,unsigned int y);

	private:

		unsigned int getWrapMode();
		unsigned int getFilterMode();
		unsigned int getTextureFormat();
		unsigned int getDataType();
	};
}
