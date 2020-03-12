#pragma once
#include "windows.h"
#include <iostream>
#include "object.h"

#define PRINT_LOG(format, ...) Console::LogFormat("[spring::log]%s:%d (%s) " format,__FILE__,__LINE__,__FUNCTION__,##__VA_ARGS__)
#define PRINT_WARNING(format, ...) Console::WarningFormat("[spring::warning]%s:%d (%s) " format,__FILE__,__LINE__,__FUNCTION__,##__VA_ARGS__)
#define PRINT_ERROR(format, ...) Console::ErrorFormat("[spring::error]%s:%d (%s) " format,__FILE__,__LINE__,__FUNCTION__,##__VA_ARGS__)

using namespace std;

namespace spring 
{
	class Console
	{
	public: 
		void static LogFormat(const char*format,...) ;
		void static WarningFormat(const char* format, ...);
		void static ErrorFormat(const char*format,... );
	};
}