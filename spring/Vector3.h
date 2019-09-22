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
		const static Vector3 one;
		const static Vector3 zero;
		const static Vector3 forward;
		const static Vector3 back;
		const static Vector3 up;
		const static Vector3 down;
		const static Vector3 left;
		const static Vector3 right;
	public:
		Vector3() 
		{
			this->x = 0.0f;
			this->y = 0.0f;
			this->z = 0.0f;
		}
		Vector3(float value) 
		{
			this->x = value;
			this->y = value;
			this->z = value;
		}
		Vector3(float x, float y, float z) 
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}

		Vector3 operator/(const float dividend);
		Vector3 operator*(const float multiplicand);
		Vector3 operator+(const Vector3 plus);
		Vector3 operator-(const Vector3 minus);
		void operator+=(const Vector3& plus);
		void operator-=(const Vector3& minus);
		void operator/=(const float dividend);
		void operator*=(const float multiplicand);
		void operator=(const Vector3& vec3);
		bool operator==(const Vector3& vec3);
		
		static float Magnitude(const Vector3 vec3);
		static Vector3 Normalize(Vector3 vec3);
		static float Dot(const Vector3 a, const Vector3 b);
		static Vector3 Cross(const Vector3 a, const Vector3 b);
		static Vector3 Lerp(const Vector3 a, const Vector3 b, const float value);
	};
}