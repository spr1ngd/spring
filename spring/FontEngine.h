#pragma once
#include "font.h"
#include "character.h"

namespace spring 
{
	class FontEngine 
	{
	public:
		FontEngine();

		static void LoadFont(Font& font);
	};
}