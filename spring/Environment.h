#pragma once
#include "color.h"

namespace spring
{
	class Environment 
	{
	public:
		class AmbientSetting 
		{
		public:
			Color color;
			AmbientSetting() 
			{
				this->color = Color(50, 50, 50, 255);
			}
		};

	public:
		static AmbientSetting ambient;
	};
}