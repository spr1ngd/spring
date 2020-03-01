#pragma once
#include "framebufferobject.h"
#include "material.h"

namespace spring 
{
	class Bloom 
	{
	public:
		FrameBufferObject* buffer;
		FrameBufferObject* bloomBuffer;
		FrameBufferObject* bloomTemp;

		Material* material;
		Material* gaussianBlurMaterial;
		Material* bloomAddMaterial;

		bool enable = false;
		float threshold = 1.0f;
		Colorf color = Colorf::white;

		Bloom();
	};
}