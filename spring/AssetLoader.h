#pragma once

namespace spring 
{
	class AssetLoader
	{
	protected:
		const char* filePath;
	public:
		void Load(const char*filePath);
	};
}