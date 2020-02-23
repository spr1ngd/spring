#pragma once
#include "GL/glew.h"
#include <vector>

using namespace std;

namespace spring 
{
	class FrameBufferObject
	{
	private:		
		static vector<FrameBufferObject*> framebuffers;

	public:
		GLuint bufferId = -1;
		GLuint rbo = -1;
		int width;
		int height;
		GLenum attachment = GL_COLOR_ATTACHMENT0;
		int level = 0;

		GLuint buffer = -1;
		unsigned int* buffers;
	public:
		FrameBufferObject( int width,int height,GLenum attachment,int level = 0);

		void Bind();
		void BindRenderbuffer();
		void CaptureMipmap(unsigned int level=0);
		void CubemapCapture(unsigned int cubemapId, unsigned int index ,unsigned int level = 0);
		void Unbind();
		void Delete();

		// color buffer
		static FrameBufferObject* GenColorFramebuffer(int width,int height,int level = 0);
		static FrameBufferObject* GenMSColorFramebuffer(int samples, int width, int height);
		static FrameBufferObject* GenHDRColorFramebuffer(int width, int height, unsigned int size = 1, int level = 0);

		static FrameBufferObject* GenDepthFramebuffer(int width, int height);
		static FrameBufferObject* GenStencilFramebuffer(int width, int height);
	};
}