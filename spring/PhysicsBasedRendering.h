#pragma once
#include "springengine.h"

namespace spring 
{
	class PhysicsBasedRendering
	{
	public:
		static Cubemap* irradiance;
		static Cubemap* prefilter;
		static Texture* prebrdf;

		static void LoadEquirectangularMap(const char* path);
		static Cubemap* CubemapConvolution(Cubemap* cubemap);

		
		static Cubemap* PreFilter(Cubemap* cubemap);
		static Texture* PreBRDF(Cubemap* cubemap);
	};
}