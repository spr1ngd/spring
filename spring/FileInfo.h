#pragma once

namespace spring 
{
	class DirectoryInfo;
	class FileInfo 
	{
	public:
		FileInfo(const char* filepath);
		~FileInfo();

		const char* Name();
		const char* Extension();
		const char* Directory();
		unsigned int Size();

		bool IsReadOnly();
		void LastModifyTime();
		void LastAccessTime();

		DirectoryInfo* GetDirectory();
	};
}