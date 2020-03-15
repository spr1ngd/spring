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

	public:
		GLuint framebufferId = -1;
		GLuint rbo = -1;	
		GLenum attachment = GL_COLOR_ATTACHMENT0;
		int level = 0;
		bool enableMRT = false; //multi render target
		bool enableHDR = false; //hight dynamic range

		GLuint buffer = -1;
		unsigned int* buffers = nullptr;
	public:
		FrameBuffer( int width,int height,GLenum attachment,int level = 0);

		void Bind();
		void BindRenderbuffer();
		void CaptureMipmap(unsigned int level=0);
		void CubemapCapture(unsigned int cubemapId, unsigned int index ,unsigned int level = 0);
		void Unbind();

		static FrameBuffer* GenMSColorFramebuffer(int width, int height, int samples); // test : why multiple sample doest not work.
		static FrameBuffer* GenHDRColorFramebuffer(int width, int height, int level = 0, unsigned int size = 1); // replaced by multiple framebuffer.
		static FrameBuffer* GenDepthFramebuffer(int width, int height); // framebuffer supports shadow buffer 

		enum DepthBuffer
		{
			NoneDepth,
			OnlyDepth,
			OnlyStencil,
			DepthWithStencil,
		};

		Texture* texture = nullptr; // binding texture
		vector<Texture*> textures; // binding multiple textures
		RenderBuffer* renderbuffer = nullptr;

		int width = 256;
		int height = 256;

		WrapMode wrap = WrapMode::ClampToEdge;
		FilterMode filter = FilterMode::Linear;
		ColorFormat colorFormat = ColorFormat::RGBA32;
		bool generateMipMap = false;
		unsigned int mipmapLevel = 0;
		AntiAliasingLevel antiAliasing = AntiAliasingLevel::Level0;
		DepthBuffer depthbuffer = DepthBuffer::NoneDepth;

		FrameBuffer(unsigned int width, unsigned int height);
		void Initialize();
		void Release();

		Colorf ReadPixel(unsigned int x,unsigned int y);

	private:
		RenderBuffer::RenderBufferFormat getRenderBufferFormat();
		unsigned int getMultiSampleLevel();
	};
}