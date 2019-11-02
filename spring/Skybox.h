#pragma once
#include <vector>
#include "cubemap.h"
#include "material.h"
#include "meshrenderer.h"

namespace spring
{
	class Skybox : public MeshRenderer
	{
	private:
		Cubemap cubemap;
	public:
		Skybox(Material* material,Cubemap cubmap);

		void SetCubemap(Cubemap cubemap);
		void Render() override;
	};
}