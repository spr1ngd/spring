#pragma once
#include "glew.h"
#include <string>
#include <map>
#include "assetloader.h"

namespace spring 
{
	class Texture;
	class TextureLoader : AssetLoader
	{
	private:
		static std::map<const char*, Texture*> textures;

	public:
		TextureLoader();
		Texture* Load(const char* filePath);
		GLuint LoadCubemap(const std::string filePaths);
		GLuint LoadCubemap(const char*right,const char*left,const char* top,const char* bottom,const char* back,const char* front);

	public:
		static Texture* GenPureWhiteTexture();
		static void Caching(const char* ,Texture* texture);
		static bool IsExist(const char* filePath ,Texture* texture);
	};
}