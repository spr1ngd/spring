#include "file.h"
#include <iostream>
#include <fstream>

using namespace spring;
using namespace std;

//char* FileIO::ReadFile(const char* filePath) 
//{
//	ifstream in(filePath, ios::in | ios::binary);
//	if (!in.good() || !in.is_open()) 
//		return nullptr;
//	in.seekg(0, ios::end);
//	int length = (int)in.tellg();
//	in.seekg(ios::beg);
//	int bufferLength = length + 1;
//	char* buffer = new char[bufferLength];
//	in.read(buffer, length);
//	buffer[length] = '\0';
//	in.close();
//	return buffer;
//}
//
//void FileIO::WriteFile(const char* filePath, const char* buffer) 
//{
//	ofstream out(filePath,ios::out);
//	if (!out) 
//	{
//		out.close();
//		return;
//	}
//	out << buffer;
//	out.close();
//}