#pragma once
#include <vector>
#include "mesh.h"
#include "modelloader.h"
#include "shader.h"
#include "material.h"
#include "transform.h"
#include "texture.h"

namespace spring 
{
	class Model
	{
	private:
		ModelLoader* loader;
	public:
		Transform* transform;

		vector<Mesh> meshes;
		vector<Texture> textures;
		Material* material;

		Model();
		Model(const char*filePath);

		void Init();
		void Render( glm::mat4 view,glm::mat4 projection );
	};
}