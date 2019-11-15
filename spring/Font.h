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
		char* name;

		Font(char* fontName);
		void AddCharacter(Character* character);
		void GetCharacter(char c);
	};
}