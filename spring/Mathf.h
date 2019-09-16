#pragma once
#include <math.h>

namespace spring 
{
	class Mathf
	{
	public:
		static float pi;
		static float e;
		static float Cos(float radian)
		{
			return (float)cos(radian);
		};
		static float Sin(float radian)
		{
			return (float)sin(radian);
		}
		static float Tan(float radian)
		{
			return (float)tan(radian);
		}
	};
}