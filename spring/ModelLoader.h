#pragma once
#include "assetloader.h"

namespace spring 
{
	class ModelLoader :public AssetLoader
	{
	private:

	public:
		ModelLoader();
		void Load(const char* filePath);
	};
}
