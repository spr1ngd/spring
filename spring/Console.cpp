#include "console.h"
#include <stdarg.h>
using namespace spring;
using namespace std;

void Console::Log(const string log) 
{
	cout << "spring::Log : " << __FILE__ << "(" << __LINE__ << ") " << log << endl;
}

void Console::Log(const char* format,...) 
{
	int ret;
	va_list va;
	va_start(va, format);
	ret = vprintf(format, va);
	va_end(va);
	// cout << "spring::Log : " << __FILE__ << "(" << __LINE__ << ") " <<  << endl;
}

void Console::Warning(const string warning)
{
	cout << "spring::Warning : " << __FILE__ << "(" << __LINE__ << ") " << warning << endl;
}

void Console::Error(const string error)
{
	cout << "spring::Error : " << __FILE__ << "(" << __LINE__ << ") " << error << endl;
}