#pragma once
#include "springengine.h"
#include <functional>

namespace spring 
{
	class Outline 
	{
	public:
		FrameBuffer* buffer;
		FrameBuffer* originBuffer;
		FrameBuffer* blendBuffer;
		FrameBuffer* outputBuffer;
		Material* outlineMaterial;
		Material* outlineBlendMaterial;
		Material* outputMateiral;

		Colorf outlineColor = Colorf(1.0f,0.455f,0.0f,1.0f);
		int outlineWidth = 2;
		bool enable = true;

		Outline();

		void Render(std::function<void()> func);
	};
}