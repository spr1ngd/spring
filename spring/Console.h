#pragma once
#include "windows.h"
#include <iostream>

using namespace std;

namespace spring 
{
	class Console
	{
	public: 
		void static Log(const char*log);
		void static LogFormat(const char*format,...) ;

		void static Warning(const char* warning);
		void static WarningFormat(const char* format, ...);

		void static Error(const char*error);
		void static ErrorFormat(const char*format,... );
	};
}