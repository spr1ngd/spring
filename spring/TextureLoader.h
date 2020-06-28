#pragma once
#include "GL/glew.h"
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
		static Texture* Load(const char* filePath, bool invertY = false);
		static Cubemap* LoadCubemap(const std::string filePaths);
		static Cubemap* LoadCubemap(const char* right, const char* left, const char* top, const char* bottom, const char* back, const char* front);

		static void SaveToBMP(const char* filePath, int width, int height, const unsigned char* pixels);
		static void SaveToBMP(const char* filepath);

	public:
		static Texture* CreateTexture(unsigned int width,unsigned int height ,unsigned int level = 0);
		static Texture* CreatePureWhiteTexture();
		static Texture* CreatePureBlackTexture();
		static Cubemap* CreateCubemap(unsigned int width,unsigned int height);
		static Cubemap* CreateCubemapMipmap(unsigned int width,unsigned int height);
		static void Caching(const char* filePath ,Texture* texture);
		static bool TryGetCache(const char* filePath , Texture* texture);
		static void Release();
	};
}