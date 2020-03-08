#pragma once
#include <string>
#include "objBase.h"

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

		static char* gen_guid() 
		{
			GUID guid;
			CoCreateGuid(&guid);
			char buffer[64];
			sprintf_s(buffer, "%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X",
				guid.Data1,guid.Data2,guid.Data3,
				guid.Data4[0], guid.Data4[1], guid.Data4[2], guid.Data4[3],
				guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7]);
			
			char* result = (char*)malloc(64 * sizeof(char));
			memset(result, 0, 64);
			strcpy_s(result, 64, buffer);
			return result;
		}
	};
}