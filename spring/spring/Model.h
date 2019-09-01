#pragma once
#include "mesh.h"
#include "modelloader.h"

namespace spring 
{
	class Model
	{
	private:
		ModelLoader loader;
	public:
		Mesh mesh;
		Model();
		Model(const char*filePath);
	};
}