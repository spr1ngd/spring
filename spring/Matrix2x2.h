#pragma once
#include "mathf.h"
#include "vector2.h"

namespace spring 
{
	class Matrix2x2 
	{
	public:
		union 
		{
			struct 
			{
				float m11, m12, m21, m22;
			};
			float m[4];
		};

	public:
		Matrix2x2(float m11, float m12, float m21, float m22);

		static Vector2 Rotate(float angle,Vector2 vec2);
		static Vector2 Scale(Vector2 scale, Vector2 vec2);
		static Vector2 Translate(Vector2 offset, Vector2 vec2);
		static Matrix2x2 Transpose(const Matrix2x2 mat2);
		static Matrix2x2 Inverse(const Matrix2x2 mat2);

		void transpose();
		void inverse();

		Matrix2x2 operator+(Matrix2x2 mat2);
		Matrix2x2 operator-(Matrix2x2 mat2);
		Vector2 operator*(const Vector2 vec2);
		Matrix2x2 operator*(Matrix2x2 mat2);
	};
}