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
	class PostProcessing : public Behaviour
	{
	private:
		void Blit(FrameBuffer* src,FrameBuffer* dst);
		void Blit(FrameBuffer* src,FrameBuffer* dst,Material* material);
		void Blit(FrameBuffer* src,FrameBuffer* dst,Material* material,unsigned int attachment);

	public:
		FrameBuffer* srcFramebuffer;
		FrameBuffer* dstFramebuffer;

		AntiAliasing* antiAliasing;
		Bloom* bloom;
		ToneMapping* toneMapping;
		Outline* outline;

		PostProcessing();
		void Initialize();

		void Preprocess();
		void Process();

		void Awake() override;
		void Update() override;
		void Destroy() override;

		TypeInfo GetTypeInfo() override 
		{
			if (nullptr == this->typeInfo)
				this->typeInfo = new TypeInfo("PostProcessing");
			return *this->typeInfo;
		}

	public:
		static PostProcessing* postprocessing;
		static FrameBuffer* outputFramebuffer;
	};
}