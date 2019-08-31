#pragma once
#include "glew.h"
#include "assetloader.h"

namespace spring 
{
	class TextureLoader : AssetLoader
	{
	public:
		TextureLoader();
		GLuint Load(const char* filePath);
	};
}