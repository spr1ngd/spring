#pragma once
#include <glm/glm.hpp>
#include "vector3.h"

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
		float& operator[] (int index);

		static Vector3 Rotate(Vector3 angle);
		static Vector3 Scale(Vector3 scale);
		static Vector3 Translate(Vector3 offset);
	};
}
