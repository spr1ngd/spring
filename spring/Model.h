#pragma once
#include <vector>
#include "mesh.h"
#include "modelloader.h"
#include "shader.h"
#include "material.h"
#include "transform.h"
#include "texture.h"
#include "renderable.h"

namespace spring 
{
	class Model : public Renderable
	{
	private:
		ModelLoader* loader;
	public:
		Transform* transform;

		vector<Mesh> meshes;
		vector<Texture> textures;
		Material* material;

		Model();
		Model(const char*filePath,Material* mateiral = nullptr);

		void Init();
		void Render() override;
	};
}