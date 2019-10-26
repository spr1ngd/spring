#pragma once
#include <glm/glm.hpp>
#include "vector2.h"
#include "vector3.h"
#include "vector4.h"
#include "mathf.h"

namespace spring 
{
	class Matrix4x4 
	{
	public:
		union 
		{
			struct 
			{
				float m11, m12, m13, m14,
					m21, m22, m23, m24,
					m31, m32, m33, m34,
					m41, m42, m43, m44;
			};
			float m[16];
		};
	public:
		Matrix4x4(float m11, float m12, float m13, float m14,
			float m21, float m22, float m23, float m24,
			float m31, float m32, float m33, float m34,
			float m41, float m42, float m43, float m44);
		Matrix4x4(const Matrix4x4& mat4);

		static Matrix4x4 indentity;

		static Vector3 Rotate(float angle,Vector3 axis,Vector3 vec3);
		static Matrix4x4 Rotate(float angle,Vector3 axis);
		static Matrix4x4 Rotate1(float angle, Vector3 axis);
		static Matrix4x4 RotateX(float angle);
		static Matrix4x4 RotateY(float angle);
		static Matrix4x4 RotateZ(float angle);

		static Vector3 Scale(Vector3 scale,Vector3 vec3);
		static Matrix4x4 Scale(float x,float y,float z);

		static Vector3 Translate(Vector3 offset,Vector3 vec3);
		static Matrix4x4 Translate(float x,float y,float z);

		static Matrix4x4 Transpose(const Matrix4x4 mat4);
		static Matrix4x4 Inverse(const Matrix4x4 mat4);

		void transpose();
		void inverse();

		float& operator[] (int index);
		Matrix4x4 operator+(const Matrix4x4 mat4);
		Matrix4x4 operator-(const Matrix4x4 mat4);
		Matrix4x4 operator*(const Matrix4x4 mat4);
		Matrix4x4 operator*(const float f);

		Vector2 operator*(const Vector2 vec2);
		Vector3 operator*(const Vector3 vec3);
		Vector4 operator*(const Vector4 vec4);
		operator float* ();
	};
}
