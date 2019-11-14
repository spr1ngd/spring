#pragma once

namespace spring 
{
	class FontEngine 
	{
	public:
		FontEngine();

		static void LoadFont(const char* fontName);
	};
}