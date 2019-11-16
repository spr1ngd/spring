#pragma once
#include <map>
#include "character.h"
#include "font.h"

namespace spring 
{
	class FontEngine 
	{
	private:
		static std::map<const char*,Font*> fonts;

	public:
		FontEngine();

		static void LoadFont(Font& font);
	};
}