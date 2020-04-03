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
	protected:
		bool initialized = false;

	public:
		bool enableGPUInstance = false;
		Mesh* mesh;
		Material* material;
		// specific material for mesh.subMesh
		// vector<Material*> materials; 
		
		MeshRenderer();
		MeshRenderer(Material* mateiral);
		~MeshRenderer();

		virtual void Initialize();
		void Render() override;
		virtual void Render( Camera* camera );
		virtual void Render( glm::mat4 view ,glm::mat4 projection);

		static MeshRenderer* GetMeshRenderer(unsigned int renderableId);
		TypeInfo GetTypeInfo() override 
		{
			if (nullptr == this->typeInfo)
				this->typeInfo = new TypeInfo("MeshRenderer");
			return *this->typeInfo;
		}
	};
}