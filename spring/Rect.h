#pragma once
#include "vector2.h"

namespace spring 
{
	namespace ui 
	{
		class Rect 
		{
		public:
			union 
			{
				struct 
				{
					float x;
					float y;
					float width;
					float height;
				};
			};

			Vector2 center;
			Vector2 position;
		public:
			Rect(float x, float y, float width, float height);
		};
	}
}