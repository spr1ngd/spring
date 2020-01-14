#pragma once 
#include "springengine.h"
#include "framebufferobject.h"
#include "fullscreenrenderer.h"
#include "antialiasing.h"
#include "bloom.h"

namespace spring 
{
	class PostProcessing
	{
	private:

		void Blit();
	public:
		FullScreenRenderer* fsRenderer;
		FrameBufferObject* srcFramebuffer;
		FrameBufferObject* dstFramebuffer;

		bool enabled;
		AntiAliasing* antiAliasing;
		Bloom* bloom;

		PostProcessing();
		void PreProcess();
		void Process();
	public:
		static PostProcessing* postprocessing;
	};
}