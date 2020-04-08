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
		static void CubemapConvolution(Cubemap* cubemap);
		static void PreFilter(Cubemap* cubemap);
		static void PreBRDF(Cubemap* cubemap);
	};
}