#pragma once
#include "glew.h"
#include "textureloader.h"

namespace spring 
{
	class Texture 
	{
	private:
		TextureLoader loader;
	public:
		GLuint textureId;
		const char* textureName;

		Texture(const char* filePath)
		{
			loader = TextureLoader();
			this->textureId = loader.Load(filePath);
			// todo : split texture name from file path
			this->textureName = filePath;
		}
	};
}
