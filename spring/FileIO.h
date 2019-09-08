#pragma once
#include <string>

namespace spring 
{
	enum WirteMode;
	class FileIO 
	{
		enum ReadMode 
		{

		};

		enum WriteMode 
		{
			Add,
			Override,
			CreateAndOverride
		};

		// base operate
	public:
		static bool CreateFile( const char*filePath );

		// file reader
	public:
		static std::string ReadAll(const char*filePath);

		// file writer
	public:
		static bool WriteAll(const char* filePath, std::string text , WriteMode writeMode = WriteMode::CreateAndOverride);
	};
}