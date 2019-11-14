#pragma once
#include <map>
#include "character.h"

using namespace std;

namespace spring
{
	class Font 
	{
	public:
		std::map<char, Character*> characters;

	public:
		Font(const char* fontName);
	};
}