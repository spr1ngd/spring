#pragma once
#include "framebufferobject.h"
#include "material.h"

namespace spring 
{
	class Bloom 
	{
	public:
		FrameBufferObject* buffer;
		Material* material;

		bool enable = false;
		float intensity = 1.0f;

		Bloom();
	};
}