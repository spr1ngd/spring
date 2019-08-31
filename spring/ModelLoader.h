#pragma once
#include "assetloader.h"

namespace spring 
{
	class ModelLoader :public AssetLoader
	{
	private:

	public:
		void Load(const char* filePath);
	};
}
