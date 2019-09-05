#pragma once
#include "mesh.h"
#include "modelloader.h"
#include "shader.h"
#include "material.h"
#include "transform.h"

namespace spring 
{
	class Model
	{
	private:
		ModelLoader loader;
	public:
		Transform* transform;
		Mesh* mesh;
		Material* material;
		Model();
		Model(const char*filePath);
		Model(Mesh* mesh, Material* material);

		void Init();
		void Render( glm::mat4 view,glm::mat4 projection );
	};
}