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
		bool enableGPUInstance = false;
		// todo : replaced vector<Mesh> by vector<Mesh*>
		vector<Mesh> meshes;
		// todo : replaced vector<Texture> by vector<Texture*>
		vector<Texture> textures;
		Material* material;
		
		MeshRenderer();
		MeshRenderer(Material* mateiral);
		~MeshRenderer();

		virtual void Init();
		void Render() override;
		virtual void Render( Camera* camera );
		virtual void Render( glm::mat4 view ,glm::mat4 projection);

		static MeshRenderer* GetMeshRenderer(unsigned int renderableId);
	};
}