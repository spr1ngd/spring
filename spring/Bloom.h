#pragma once
#include "framebuffer.h"
#include "material.h"

namespace spring 
{
	class Bloom 
	{
	public:
		FrameBuffer* buffer;
		FrameBuffer* bloomBuffer;
		FrameBuffer* bloomTemp;

		Material* material;
		Material* gaussianBlurMaterial;
		Material* bloomAddMaterial;

		bool enable = false;
		float threshold = 1.0f;
		Colorf color = Colorf::white;

		Bloom();
	};
}