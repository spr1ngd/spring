#pragma once
#include <glew.h>
#include "vector2.h"

namespace spring 
{
	class MaterialTexture 
	{
	public:
		GLuint texture;
		Vector2 tilling = Vector2::one;
		Vector2 offset = Vector2::zero;

		MaterialTexture();
	};
}