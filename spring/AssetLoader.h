#pragma once

namespace spring 
{
	class AssetLoader
	{
	private:

	protected:
		const char* filePath;
	public:
		void Load(const char*filePath);
		static void Release();
	};
}