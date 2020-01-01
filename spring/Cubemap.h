#pragma once
#include "glew.h"
#include <vector>

using namespace std;

namespace spring 
{
	class Cubemap 
	{
	public:
		GLuint cubemap;
		unsigned int level;
		unsigned int width;
		unsigned int height;

	public:
		Cubemap();
	};
}