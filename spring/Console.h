#pragma once
#include <iostream>

namespace spring 
{
	class Console
	{
	public:
		void static Log(const char* log);
		void static Error(const char* error);
		void static Warning(const char* warning);
	};
}