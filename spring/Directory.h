#pragma once
#include <filesystem> 

namespace spring 
{
	class DirectoryInfo;
	class FileInfo;
	class Directory 
	{
	public:
		static bool Exist(const char* directory);
		static bool Create(const char* directory);
		static bool Delete(const char* directroy);

		static bool CopyTo(const char* srcDir,const char* dstDir);
		static bool MoveTo(const char* srcDir,const char* dstDir);

		static DirectoryInfo* GetDiectorie(const char* directory);
		static FileInfo* GetFiles(const char* directory,bool recursive);
	};
}