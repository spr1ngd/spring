#pragma once 
#include "skybox.h"
#include "camera.h"
#include "framebuffer.h"

namespace spring 
{
	class Texture;
	class Material;
	class FullScreenRenderer;
	class FrameBuffer;
	class Graphic 
	{
	private:
		static FullScreenRenderer* fsRenderer;
		static void Initialize();

	public:
		static void Blit(FrameBuffer& source, FrameBuffer& destination);
		static void Blit(FrameBuffer& source, FrameBuffer& destination, Material& material);
		static void Blit(FrameBuffer& source, FrameBuffer& destination, Material& material, unsigned int attachment);
	};
}