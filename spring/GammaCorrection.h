#pragma once
#include "postprocessing.h"

namespace spring 
{
	namespace FX 
	{
		class GammaCorrection : public PostProcessingFX
		{
		public:
			float gamma;
			GammaCorrection();

			void Initialize() override;
			void Release() override;
			void Process(FrameBuffer& srouce, FrameBuffer& destination) override;
		};
	}
}