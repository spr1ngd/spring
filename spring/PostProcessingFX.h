#pragma once

namespace spring 
{
	class Material;
	class FrameBuffer;
	namespace FX
	{
		class PostProcessingFX 
		{
		public:
			const char* fxType;
			Material* material;
			bool enable = false;

			PostProcessingFX();

			void virtual Initialize();
			void virtual Release();
			void virtual Process(FrameBuffer& srouce,FrameBuffer& destination);
		};
	}
}