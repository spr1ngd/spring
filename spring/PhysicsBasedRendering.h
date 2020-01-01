#pragma once
#include "springengine.h"

namespace spring 
{
	class PhysicsBasedRendering
	{
	public:
		// load equirectangular map and transfer it to cubemap
		static void LoadEquirectangularMap(const char* path);
		// folding cubemap
		static Cubemap* CubemapConvolution(Cubemap* cubemap);
	};
}