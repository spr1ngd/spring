#pragma once
#include "material.h"
#include "framebufferobject.h"

namespace spring 
{
	class ToneMapping 
	{
	public:
		FrameBufferObject* buffer;
		Material* material;

		float exposure = 1.0f;
		bool enable = true;

		ToneMapping();
	};
}