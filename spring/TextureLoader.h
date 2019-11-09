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
		static Texture* Load(const char* filePath, bool invertY = false);
		static Cubemap* LoadCubemap(const std::string filePaths);
		static Cubemap* LoadCubemap(const char* right, const char* left, const char* top, const char* bottom, const char* back, const char* front);

		static void SaveToBMP(const char* filePath, int width, int height, const unsigned char* pixels);
		static void SaveToBMP(const char* filepath);

	public:
		static Texture* GenPureWhiteTexture();
		static void Caching(const char* filePath ,Texture* texture);
		static bool IsExist(const char* filePath ,Texture* texture);
	};
}