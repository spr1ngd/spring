#pragma once
#include <exception>

using namespace std;

namespace spring 
{
	struct NotImplementException  : public exception
	{
		const char* what() const throw()
		{
			return "Not implement.";
		}
	};
}