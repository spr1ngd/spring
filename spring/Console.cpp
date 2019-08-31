#include "Console.h"
using namespace spring;
using namespace std;

void Console::Log(const char* log) 
{
	cout << "spring::Log : " << __FILE__ << "(" << __LINE__ << ") " << log << endl;
}

void Console::Warning(const char* warning) 
{
	cout << "spring::Warning : " << __FILE__ << "(" << __LINE__ << ") " << warning << endl;
}

void Console::Error(const char* error) 
{
	cout << "spring::Error : " << __FILE__ << "(" << __LINE__ << ") " << error << endl;
}