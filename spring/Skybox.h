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
	public:
		static Cubemap* irradianceCubemap;
		Cubemap* cubemap;
		Skybox(Material* material,Cubemap* cubmap);

		void SetCubemap(Cubemap* cubemap);
		void Render() override;
	};
}