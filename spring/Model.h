#pragma once
#include "mesh.h"
#include "modelloader.h"
#include "shader.h"
#include "material.h"

namespace spring 
{
	class Model
	{
	private:
		ModelLoader loader;
	public:
		Mesh* mesh;
		Material* material;
		Model();
		Model(const char*filePath);
		Model(Mesh* mesh, Material* material);

		void Init();
		void Render();
	};
}