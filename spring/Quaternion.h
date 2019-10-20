#pragma once
#include "mathf.h"
#include "vector3.h"

namespace spring 
{
	class Quaternion 
	{
	public:
		union
		{
			struct
			{
				float x, y, z, w;
			};
		};
		static Quaternion indentity;
	public:
		Quaternion(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 1.0f);

		float Angle() const;
		float Magnitude() const;
		void Normalize();
		Vector3 AngleAxis() const;
		Vector3 Eulerangle() const ;

		static Quaternion RotateX(float theta);
		static Quaternion RotateY(float theta);
		static Quaternion RotateZ(float theta);
		static Quaternion Rotate(Vector3 axis,float theta);

		static Quaternion Euler(const Vector3& eulerangle);
		static Quaternion Normalize(const Quaternion &quaternion);
		static Quaternion Conjugate(const Quaternion &quaternion);

		Quaternion operator*(const Quaternion &a);
		Quaternion operator*=(const Quaternion &a);
	};
}

