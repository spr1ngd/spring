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
				this->color = Color::gray;
			}
		};

	public:
		static AmbientSetting ambient;
	};
}