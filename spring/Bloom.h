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

		Material* material;
		Material* gaussianBlurMaterial;

		bool enable = false;

		Bloom();
	};
}