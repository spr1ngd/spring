#pragma once

namespace spring 
{
	class FileInfo;
	class DirectoryInfo
	{
	public:
		DirectoryInfo(const char* directory);
		~DirectoryInfo();

		const char* Name();
		unsigned int Size();
		
		DirectoryInfo* GetParentDirectory();
		DirectoryInfo* GetDirectory(const char* folderName);
		DirectoryInfo* GetDirectories(bool recursive = false);

		FileInfo* GetFile(const char* fileName);
		FileInfo* GetFiles(bool recursive = false);
	};
}