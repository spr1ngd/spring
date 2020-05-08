#pragma once
#include "mathf.h"
#include "vector3.h"
#include "matrix4x4.h"

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
		Quaternion()
		{
			this->x = 0.0f;
			this->y = 0.0f;
			this->z = 0.0f;
			this->w = 0.0f;
		}
		Quaternion(float x, float y , float z, float w);
		 
		float Magnitude() const;
		void Normalize(); 
		Vector3 EulerAngle() const ;

		static Quaternion RotateX(float theta);
		static Quaternion RotateY(float theta);
		static Quaternion RotateZ(float theta);
		static Quaternion Rotate(Vector3 axis,float theta);

		static Quaternion Euler(const Vector3& eulerangle);
		static Quaternion Euler(float x, float y, float z);
		static Quaternion Normalize(const Quaternion& rotation);
		static Quaternion Conjugate(const Quaternion& rotation);

		static Matrix4x4 ToRotationMatrix(const Quaternion& rotation);

		Quaternion operator*(const Quaternion& a);
		Quaternion operator*=(const Quaternion& a);
		Vector3 operator*(const Vector3& vec3);

		const char* ToString();
	};
}

