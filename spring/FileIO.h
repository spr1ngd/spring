#pragma once

namespace spring 
{
	class FileIO 
	{
	public:
		static char* ReadFile(const char* filePath);
		static void WriteFile(const char* filePath,const char* buffer);
	};
}