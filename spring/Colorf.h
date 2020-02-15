#pragma once
#include "color.h"

namespace spring
{
	class Color;
	class Colorf 
	{
	public:
		union 
		{
			struct 
			{
				float r, g, b, a;
			};
		};
		static Colorf red;
		static Colorf green;
		static Colorf blue;
		static Colorf yellow;
		static Colorf cyan;
		static Colorf megenta;
		static Colorf white;
		static Colorf black;
		static Colorf gray;

		static Colorf Lerp(Colorf a,Colorf b,const float value);

	public:
		Colorf();
		Colorf(float c);
		Colorf(float r, float g, float b, float a);

		void operator= (const Color value);
		void operator= (const Colorf value);
		Colorf operator+ (const Colorf value);
		Colorf operator- (const Colorf value);
		Colorf operator* (const float f);
		Colorf operator/ (const float f);
	};
}
