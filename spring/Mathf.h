#pragma once
#include <math.h>
#include <matrix2x2.h>
#include <matrix4x4.h>

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
		static float Radian(float angle) 
		{
			return (angle / 180.0f) * Mathf::pi;
		}
		static float Angle(float radian) 
		{
			return (radian / Mathf::pi) * 180.0f;
		}

		static int Clamp(int value, int min, int max)
		{
			if (value < min)
				return min;
			if (value > max)
				return max;
			return value;
		};
		static float Clamp(float value, float min, float max)
		{
			if (value < min)
				return min;
			if (value > max)
				return max;
			return value;
		}
	};
}