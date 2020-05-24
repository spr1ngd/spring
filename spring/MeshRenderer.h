#pragma once
#include <vector>
#include "node.h"
#include "renderable.h"
#include "material.h"
#include "mesh.h"

namespace spring 
{
	class Camera;
	class MeshRenderer : public Node, public Renderable
	{
	protected:
		bool initialized = false;

	public:
		bool enableGPUInstance = false;
		Mesh* mesh;
		Material* material;
		
		MeshRenderer();
		MeshRenderer(Material* mateiral);
		~MeshRenderer() override;

		virtual void Initialize();
		void Render() override;
		virtual void Render( Camera* camera );
		virtual void Render( const glm::mat4& view ,const glm::mat4& projection ,const glm::mat4& vp);
		virtual void RenderMesh(Material* mat,Mesh* mesh,const glm::mat4& mode,const glm::mat4& nm,const glm::mat4& view,const glm::mat4& projection ,const glm::mat4& mvp);

		TypeInfo GetTypeInfo() override 
		{
			if (nullptr == this->typeInfo)
				this->typeInfo = new TypeInfo("MeshRenderer");
			return *this->typeInfo;
		}
		void Destroy() override;

		static MeshRenderer* GetMeshRenderer(unsigned int renderableId);
	};
}