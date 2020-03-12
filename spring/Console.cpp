#include "console.h"
#include <stdarg.h>

using namespace spring;
using namespace std;

void Console::LogFormat(const char* format,...) 
{
	int ret;
	va_list va;
	va_start(va, format);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	cout << "";
	ret = vprintf(format, va);
	cout << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
	va_end(va);
}

void Console::WarningFormat(const char* format, ...)
{
	int ret;
	va_list va;
	va_start(va, format);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
	cout << "";
	ret = vprintf(format, va);
	cout << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
	va_end(va);
}

void Console::ErrorFormat(const char* format, ...)
{
	int ret;
	va_list va;
	va_start(va, format);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
	cout << "";
	ret = vprintf(format, va);
	cout << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
	va_end(va);
}