#pragma once
#include "postprocessing.h"

namespace spring 
{
	class Texture;
	namespace FX 
	{
		class Vignette : public PostProcessingFX
		{
		public :
			enum VignetteType 
			{
				Classical = 0,
				Mask = 1
			};

			int vignetteType = VignetteType::Classical;
			Colorf color;
			Vector2 center;
			float intensity;
			float smoothness;
			float roundness;
			bool rounded;
			Texture* maskTex = nullptr;

			Vignette();

			void Initialize() override;
			void Release() override;
			void Process(FrameBuffer& source,FrameBuffer& destination) override;
		};
	}
}