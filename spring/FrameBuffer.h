#pragma once
#include "GL/glew.h"
#include <vector>
#include "texture.h"
#include "renderbuffer.h"
#include "console.h"
#include "colorf.h"

using namespace std;

namespace spring 
{
	class FrameBuffer
	{
	private:		
		static vector<FrameBuffer*> framebuffers;

		unsigned int buffersSize = 1;
		vector<Texture*> textures; // binding multiple textures
		RenderBuffer* renderbuffer = nullptr;
		GLuint rbo = -1;

		RenderBuffer::RenderBufferFormat getRenderBufferFormat();
		unsigned int getMultiSampleLevel();
	public:
		enum DepthBuffer
		{
			NoneDepth,
			OnlyDepth,
			OnlyStencil,
			DepthWithStencil,
		};

		GLuint framebufferId = -1;
		int width = 256;
		int height = 256;
		WrapMode wrap = WrapMode::ClampToEdge;
		FilterMode filter = FilterMode::Linear;
		ColorFormat colorFormat = ColorFormat::RGBA32;
		bool generateMipMap = false;
		unsigned int mipmapLevel = 0;
		AntiAliasingLevel antiAliasing = AntiAliasingLevel::Level0;
		DepthBuffer depthbuffer = DepthBuffer::NoneDepth;

		FrameBuffer(unsigned int width, unsigned int height,ColorFormat colorformat = ColorFormat::RGB24,unsigned int bufferSize = 1);

		void Initialize();
		void Release();
		void Bind();
		void Unbind();
		void BindRenderbuffer();
		unsigned int GetBuffer(unsigned int index = 0);
		Colorf ReadPixel(unsigned int x,unsigned int y);
		void CaptureMipmap(unsigned int level = 0);
		void CubemapCapture(unsigned int cubemapId, unsigned int index, unsigned int level = 0);

		void Blit(FrameBuffer& dst);
	};
}