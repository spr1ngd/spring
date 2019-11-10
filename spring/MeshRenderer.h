#pragma once
#include <vector>
#include "mesh.h"
#include "node.h"
#include "shader.h"
#include "transform.h"
#include "texture.h"
#include "renderable.h"
#include "material.h"
#include "camera.h"

namespace spring 
{
	class MeshRenderer : public Node, public Renderable
	{
	private:
	public:
		vector<Mesh> meshes;
		vector<Texture> textures;
		Material* material;

		MeshRenderer();
		MeshRenderer(Material* mateiral);
		void Init();
		void Render() override;
		void Render( Camera* camera );
	};
}