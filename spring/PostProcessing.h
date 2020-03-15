#pragma once 
#include "springengine.h"
#include "framebuffer.h"
#include "fullscreenrenderer.h"
#include "antialiasing.h"
#include "bloom.h"
#include "tonemapping.h"
#include "outline.h"

namespace spring 
{
	class PostProcessing
	{
	private:
		void Blit(FrameBuffer* src,FrameBuffer* dst);
		void Blit(FrameBuffer* src,FrameBuffer* dst,Material* material);
		void Blit(FrameBuffer* src,FrameBuffer* dst,Material* material,unsigned int attachment);

	public:

		FullScreenRenderer* fsRenderer;
		FrameBuffer* srcFramebuffer;
		FrameBuffer* dstFramebuffer;

		bool enabled;
		AntiAliasing* antiAliasing;
		Bloom* bloom;
		ToneMapping* toneMapping;
		Outline* outline;

		PostProcessing();
		void Initialize();

		void Preprocess();
		void Process();
	public:
		static PostProcessing* postprocessing;
		static FrameBuffer* outputFramebuffer;
	};
}