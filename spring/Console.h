#pragma once
#include <iostream>
#include <string>

using namespace std;

namespace spring 
{
	class Console
	{
	public:
		void static Log(const string log);
		void static Log(const char* format,...) ;
		void static Error(const string error);
		void static Warning(const string warning);
	};
}