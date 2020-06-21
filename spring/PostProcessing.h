#pragma once 
#include <map>
#include "springengine.h"
#include "framebuffer.h"
#include "fullscreenrenderer.h"
#include "antialiasing.h"
#include "postprocessingfx.h"
#include "vignette.h"

#include "bloom.h"
#include "tonemapping.h"
#include "outline.h"

using namespace spring::FX;

namespace spring 
{
	const char* PostProcessingVignette = "Vignette";

	class PostProcessing : public Behaviour
	{
	private:

		std::map<const char*, PostProcessingFX*> effects;
		PostProcessingFX* GetFX(const char* fxType)
		{
			auto item = this->effects.find(fxType);
			if (item == this->effects.end())
				return nullptr;
			return item->second;
		}

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

		template <typename T>
		T* AddFX() 
		{
			T* t = new T();
			PostProcessingFX* fx = (PostProcessingFX*)t; // TODO: how to get type name without type instance.
			auto item = this->effects.find(fx->fxType);
			if (item != this->effects.end())
			{
				delete fx;
				return item->second;
			}
			fx->Initialize();
			this->effects.insert(fx->fxType, fx);
		}

		template <typename T>
		void RemoveFX() 
		{
			T* t = new T();
			PostProcessingFX* fx = (PostProcessingFX*)t;  // TODO: how to get type name without type instance.
			auto item = this->effects.find(fx->fxType);
			if (item != this->effects.end())
			{
				item->second->Release();
				delete item->second;
				this->effects.erase(item);
			}
			delete fx;
		}


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