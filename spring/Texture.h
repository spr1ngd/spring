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
		GLuint textureId = -1;
		const char* textureName = "";
		const char* textureType = "";

		Texture();
		Texture(const char* filePath)
		{
			loader = TextureLoader();
			this->textureId = loader.Load(filePath);
		}

		void Load( const char* filePath ) 
		{
			loader = TextureLoader();
			this->textureId = loader.Load(filePath);
		};
	};
}
