#pragma once
#include "glew.h"
#include <vector>

using namespace std;

namespace spring 
{
	class FrameBufferObject
	{
	private:		
		static vector<FrameBufferObject*> framebuffers;

		FrameBufferObject( int width,int height,GLenum attachment,int level = 0);
	public:
		GLuint bufferId = -1;
		int width;
		int height;
		GLenum attachment = GL_COLOR_ATTACHMENT0;
		int level = 0;

		GLuint colorbuffer = -1;
	public:
		void Bind();
		void Unbind();
		void Delete();

		static FrameBufferObject* GenColorFramebuffer(int width,int height,int level = 0);
		static FrameBufferObject* GenDepthFramebuffer(int width, int height);
		static FrameBufferObject* GenStencilFramebuffer(int width, int height);
	};
}