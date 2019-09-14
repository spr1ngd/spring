#pragma once
#include <vector>
#include "node.h"
#include "model.h"
#include "material.h"
#include "transform.h"
#include "renderable.h"

namespace spring
{
	class Skybox : public Node, public Renderable
	{
	private:
		Model* skybox;
		ModelLoader* loader;
	public:
		Transform* transform;
		Material* material;
		vector<Mesh> meshes;
		vector<Texture> textures;
		Skybox(const char* skyboxName, Material* material = nullptr);

		void Init();
		void Render() override;
	};
}