#pragma once
#include <vector>
#include "cubemap.h"
#include "material.h"
#include "meshrenderer.h"

namespace spring
{
	class Texture;
	class Skybox : public MeshRenderer
	{
	private:
	public:
		static Cubemap* irradianceCubemap;
		static Cubemap* prefilter;
		static Texture* prebrdf;
		Cubemap* cubemap;
		Skybox();
		Skybox(Material* material,Cubemap* cubmap);

		void SetCubemap(Cubemap* cubemap);
		void Render() override;
	};
}