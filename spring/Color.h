#pragma once
#include "colorf.h"

namespace spring 
{
	class Color
	{
	public:
		union
		{
			struct
			{
				unsigned char r, g, b, a;
			};
		};

		static Color black;
		static Color white;
		static Color red;
		static Color green;
		static Color blue;
		static Color yellow;
		static Color cyan;
		static Color magenta;
		static Color gray;

	public:
		Color();
		Color(unsigned char color);
		Color(unsigned char r,unsigned char g,unsigned char b,unsigned char a);
	};
}