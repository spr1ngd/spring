#pragma once
#include "colorf.h"

namespace spring 
{
	class Colorf;
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
		static Color clear;

		static Color Lerp(Color a,Color b,const float value);

	public:
		Color();
		Color(unsigned char color);
		Color(unsigned char r,unsigned char g,unsigned char b,unsigned char a);

		void operator= (const Colorf value);
		void operator= (const Color value);
		Color operator+ (const Color value);
		Color operator- (const Color value);
		Color operator* (const float f);
		Color operator/ (const float f);
	};
}