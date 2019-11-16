#pragma once
#include <map>
#include "character.h"

using namespace std;

namespace spring
{
	class Font 
	{
	private:
		std::map<char, Character*> characters;

	public:
		const char* name;

		Font(const char* fontName);
		void AddCharacter(Character* character);
		Character* GetCharacter(char c);
	};
}