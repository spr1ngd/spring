#pragma once
#include "glew.h"
#include "assetloader.h"
#include <string>

namespace spring 
{
	class TextureLoader : AssetLoader
	{
	public:
		TextureLoader();
		GLuint Load(const char* filePath);
		GLuint LoadCubemap(const std::string filePaths);
		GLuint LoadCubemap(const char*right,const char*left,const char* top,const char* bottom,const char* back,const char* front);
	};
}