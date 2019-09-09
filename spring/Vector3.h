#pragma once
#include <math.h>

namespace spring 
{
	class Vector3
	{
	public:
		union 
		{
			struct 
			{
				float x, y, z;
			};
		};
	public:
		Vector3(float x = 0.0f, float y = 0.0f, float z = 0.0f) 
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}
		static float Magnitude(const Vector3 vec3);
		static Vector3 Normalize(Vector3 vec3);
		static float Dot(const Vector3 a,const Vector3 b);
		static Vector3 Cross(const Vector3 a,const Vector3 b);

		Vector3 operator/(const float dividend);
		Vector3 operator*(const float multiplicand);
		Vector3 operator+(const Vector3 plus);
		Vector3 operator-(const Vector3 minus);
	};
}