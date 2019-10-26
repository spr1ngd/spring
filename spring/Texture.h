#pragma once
#include "glew.h"
#include "textureloader.h"

namespace spring 
{
	class TextureLoader;
	class Texture 
	{
	private:
		TextureLoader loader;
	public:
		GLuint textureId = -1;
		const char* textureName = "";
		const char* textureType = "";

		Texture();
		Texture(const char* filePath);
		void Load(const char* filePath);
	};
}
