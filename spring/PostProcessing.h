#pragma once 
#include "springengine.h"
#include "framebufferobject.h"
#include "fullscreenrenderer.h"
#include "antialiasing.h"
#include "bloom.h"
#include "tonemapping.h"

namespace spring 
{
	class PostProcessing
	{
	private:
		void Blit(FrameBufferObject* src,FrameBufferObject* dst);
		void Blit(FrameBufferObject* src,FrameBufferObject* dst,Material* material);
		void Blit(FrameBufferObject* src,FrameBufferObject* dst,Material* material,unsigned int attachment);

	public:

		FullScreenRenderer* fsRenderer;
		FrameBufferObject* srcFramebuffer;
		FrameBufferObject* dstFramebuffer;

		bool enabled;
		AntiAliasing* antiAliasing;
		Bloom* bloom;
		ToneMapping* toneMapping;

		PostProcessing();
		void Initialize();

		void Preprocess();
		void Process();
	public:
		static PostProcessing* postprocessing;
		static FrameBufferObject* outputFramebuffer;
	};
}