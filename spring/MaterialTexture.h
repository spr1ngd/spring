#pragma once
#include "GL/glew.h"
#include "vector2.h"

namespace spring 
{
	class MaterialTexture 
	{
	public:
		unsigned texture = -1;
		Vector2 tilling = Vector2::one;
		Vector2 offset = Vector2::zero;

		MaterialTexture();
	};
}