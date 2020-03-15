#pragma once

namespace spring 
{
	class RenderBuffer 
	{
	public:
		enum RenderBufferFormat
		{
			Depth,
			Stencil,
			DepthWithStencil
		};

		unsigned int buffer = -1;
		unsigned int width = 256;
		unsigned int height = 256;
		unsigned int multiSampleLevel = 0;
		RenderBufferFormat format = RenderBufferFormat::DepthWithStencil;

		RenderBuffer(unsigned int width, unsigned int height, RenderBufferFormat format = RenderBufferFormat::DepthWithStencil);
		void Initialize();
		void Release();

	private:
		unsigned int getFormat();
		unsigned int getAttachment();
	};
}