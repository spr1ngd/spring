#pragma once
#include <math.h>
#include <ctime>
#include <matrix2x2.h>
#include <matrix4x4.h>

namespace spring 
{
	class Mathf
	{
	public:
		static float pi;
		static float e;

		#pragma region Trigonometric functions

		static float Cos(float radian)
		{
			return (float)cos(radian);
		};
		static float Acos( float cos )   
		{
			return acosf(cos);
		}

		static float Sin(float radian)
		{
			return (float)sin(radian);
		}
		static float Asin( float sin )
		{
			return asinf(sin);
		}

		static float Tan(float radian)
		{
			return (float)tan(radian);
		}
		static float Atan(float tan) 
		{
			return atan(tan);
		}
		static float Atan2(float y, float x)
		{
			return atan2(y, x);
		}

		static float Radian(float angle) 
		{
			return (angle / 180.0f) * Mathf::pi;
		}
		static float Angle(float radian) 
		{
			return (radian / Mathf::pi) * 180.0f;
		}

		#pragma endregion

		#pragma region Basic operation

		static float Pow( float value, float p ) 
		{
			return pow(value, p);
		}

		static float Sqrt(float value)
		{
			return sqrtf(value);
		}

		static char Abs(char value)
		{
			if (value < 0)
				return -value;
			return value;
		}
		static int Abs(int value)
		{
			if (value < 0)
				return -value;
			return value;
		}
		static float Abs(float value)
		{
			if (value < 0.0f)
				return -value;
			return value;
		}
		static double Abs(double value)
		{
			if (value < 0.0)
				return -value;
			return value;
		}

		static float Clamp01(float value)
		{
			return Clamp(value, 0.0f, 1.0f);
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

		#pragma endregion

		#pragma region  Numeric random value
		 
		static void RandomSeed()
		{
			srand((unsigned int)time(NULL));
		}
		static int Random(int min, int max) 
		{
			return min + rand() % (max - min);
		}
		static unsigned int Random(unsigned int min, unsigned int max) 
		{
			return min + rand() % (max - min);
		}
		static float Randomf() 
		{
			return rand() / float(RAND_MAX);
		}

		static float Randomf(float min, float max)
		{
			return min + Randomf() * (max - min);
		}

		#pragma endregion
	};
}