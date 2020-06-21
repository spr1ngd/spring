#pragma once
#include <filesystem> 

namespace spring 
{
	class FileInfo;
	class File
	{
	public:
		static bool Exist(const char* filepath);
		static bool Create(const char* filepath);
		static bool Delete(const char* filepath);
		static bool CopyTo(const char* src,const char* dst);
		static bool MoveTo(const char* srd,const char* dst);

		static char* Read(const char* filepath);
		static bool Write(const char* filepath,const char* content);

		static FileInfo* GetFile(const char* filepath);
	};
}