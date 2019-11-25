#pragma once
#include "springengine.h"
#include <vector>

namespace spring
{
	class InstancedRenderer : public MeshRenderer
	{
	private:
		std::vector<Transform*> instances;
		std::vector<glm::mat4> matrixes;
		std::vector<glm::mat4> normalmatrixes;
	public:
		Mesh mesh;

		InstancedRenderer();
		InstancedRenderer(Material* instancedMaterial);

		void Init() override;
		void Render(Camera* camera) override;
		void AddInstance(Vector3 position,Vector3 eulerangle,Vector3 scale);
	};
}