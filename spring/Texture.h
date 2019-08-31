#pragma once
#include "glew.h"
#include "textureloader.h"

namespace spring 
{
	class Texture 
	{
	private:
		TextureLoader loader;
	public:
		GLuint textureId;
		const char* textureName;
	};
}
