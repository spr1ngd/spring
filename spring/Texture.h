#pragma once
#include "glew.h"
#include "textureloader.h"

namespace spring 
{
	class TextureLoader;
	class Texture 
	{
	public:
		GLuint textureId = -1;
		const char* textureName = "";
		const char* textureType = "";
		unsigned int width;
		unsigned int height;

		Texture();
		Texture(const char* filePath);
		void Load(const char* filePath);
		void Release();
	};
}
