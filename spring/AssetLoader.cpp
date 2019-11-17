#include "assetloader.h"
#include "textureloader.h"

using namespace spring;

void AssetLoader::Load(const char* filePath) 
{

}

void AssetLoader::Release() 
{
	TextureLoader::Release();
}