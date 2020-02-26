#pragma once
#include <string>

namespace spring 
{
	class misc 
	{
	public:

		static char* string2c(std::string str) 
		{
			const char* c = str.c_str();
			char* result = new char[strlen(c)];
			strcpy_s(result, strlen(c) + 1, c);
			return result;
		}
	};
}