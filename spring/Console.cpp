#include "console.h"
#include <stdarg.h>

using namespace spring;
using namespace std; 

void Console::Log(const char* log)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	cout << "spring::Log : " << __FILE__ << "(" << __LINE__ << ") " << log << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY );
}

void Console::Log(spring::Object& obj) 
{
	const char* log = obj.ToString();
	Console::Log(log);
}

void Console::LogFormat(const char* format,...) 
{
	int ret;
	va_list va;
	va_start(va, format);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	cout << "spring::Log : " << __FILE__ << "(" << __LINE__ << ") ";
	ret = vprintf(format, va);
	cout << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
	va_end(va);
}

void Console::Warning(const char* warning)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
	cout << "spring::Warning : " << __FILE__ << "(" << __LINE__ << ") " << warning << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
}

void Console::Warning(Object& obj) 
{
	const char* log = obj.ToString();
	Console::Warning(log);
}

void Console::WarningFormat(const char* format, ...)
{
	int ret;
	va_list va;
	va_start(va, format);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
	cout << "spring::Warning : " << __FILE__ << "(" << __LINE__ << ") ";
	ret = vprintf(format, va);
	cout << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
	va_end(va);
}

void Console::Error(const char* error)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
	cout << "spring::Error : " << __FILE__ << "(" << __LINE__ << ") " << error << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
}

void Console::Error(Object& obj) 
{
	const char* log = obj.ToString();
	Console::Error(log);
}

void Console::ErrorFormat(const char* format, ...)
{
	int ret;
	va_list va;
	va_start(va, format);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
	cout << "spring::Error : " << __FILE__ << "(" << __LINE__ << ") ";
	ret = vprintf(format, va);
	cout << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
	va_end(va);
}