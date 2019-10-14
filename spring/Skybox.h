#pragma once
#include <vector>
#include "node.h"
#include "meshrenderer.h"
#include "material.h"
#include "transform.h"
#include "renderable.h"

namespace spring
{
	class Skybox : public Node, public Renderable
	{
	private:
		GLuint cubemap;
	public:
		Transform* transform;
		Material material;
		vector<Mesh> meshes;
		vector<Texture> textures;
		Skybox(const char* skyboxName, Material material);

		void Init();
		void Render() override;
	};
}