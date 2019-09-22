#pragma once
#include "color.h"

namespace spring
{
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

	public:
		Colorf();
		Colorf(float c);
		Colorf(float r, float g, float b, float a);

		
	};
}
