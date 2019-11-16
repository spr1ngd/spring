#pragma once
#include "vector2.h"
#include "texture.h"

namespace spring 
{
	class Character
	{
	public:
		char c;
		Texture* character;
		Vector2 size;
		Vector2 bearing;
		GLuint advance;

	public:
		Character();
	};
}