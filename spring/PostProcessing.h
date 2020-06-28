#pragma once 
#include <map>
#include "springengine.h"
#include "framebuffer.h"
#include "fullscreenrenderer.h"
#include "antialiasing.h"
#include "postprocessingfx.h"
#include "vignette.h"
#include "gammacorrection.h"

#include "bloom.h"
#include "tonemapping.h"
#include "outline.h"

using namespace spring::FX;

namespace spring
{

	class PostProcessing : public Behaviour
	{
	private:

		std::map<const char*, PostProcessingFX*> effects;

		void Blit(FrameBuffer* src,FrameBuffer* dst);
		void Blit(FrameBuffer* src,FrameBuffer* dst,Material* material);
		void Blit(FrameBuffer* src,FrameBuffer* dst,Material* material,unsigned int attachment); 

	public:
		static const char* PostProcessingVignette;
		static const char* PostProcessingGammaCorrection;

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
				return (T*)item->second;
			}
			fx->Initialize();
			this->effects.insert(std::pair<const char*,PostProcessingFX*>(fx->fxType, fx));
			return (T*)fx;
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

		template <typename T>
		T* GetFX() 
		{
			T* t = new T();
			PostProcessingFX* fx = (PostProcessingFX*)t;
			PostProcessingFX* result = this->GetFX(fx->fxType);
			delete fx;
			if (nullptr == result)
				return nullptr;
			return (T*)result;
		}

		PostProcessingFX* GetFX(const char* fxType)
		{
			auto item = this->effects.find(fxType);
			if (item == this->effects.end())
				return nullptr;
			return item->second;
		}

		template <typename T>
		T* SetFX(bool enable) 
		{
			T* t = this->GetFX<T>();
			if (nullptr == t)
				t = this->AddFX<T>();
			PostProcessingFX* fx = (PostProcessingFX*)t;
			fx->enable = enable;
			return t;
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