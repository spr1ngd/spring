#pragma once
#include "glew.h"
#include <string>
#include <map>
#include "assetloader.h"
#include "cubemap.h"

namespace spring 
{
	class Texture;
	class TextureLoader : AssetLoader
	{
	private:
		static std::map<const char*, Texture*> textures;
		static std::vector<Cubemap*> cubemaps;

	public:
		TextureLoader();
		Texture* Load(const char* filePath , bool invertY = false);
		Cubemap* LoadCubemap(const std::string filePaths);
		Cubemap* LoadCubemap(const char*right,const char*left,const char* top,const char* bottom,const char* back,const char* front);

	public:
		static Texture* GenPureWhiteTexture();
		static void Caching(const char* filePath ,Texture* texture);
		static bool IsExist(const char* filePath ,Texture* texture);
	};
}