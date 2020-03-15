#pragma once
#include "material.h"
#include "framebuffer.h"

namespace spring 
{
	class ToneMapping 
	{
	public:
		FrameBuffer* buffer;
		Material* material;

		float exposure = 1.0f;
		bool enable = true;

		ToneMapping();
	};
}