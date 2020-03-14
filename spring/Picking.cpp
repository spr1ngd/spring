#include "picking.h"

using namespace spring;

bool Picking::enable;
FrameBufferObject* Picking::colorbuffer;
Material* Picking::material;

Picking::Picking()
{

}

void Picking::Initialize() 
{
	if (!enable)
		return;
	colorbuffer = FrameBufferObject::GenColorFramebuffer(Screen::width, Screen::height, 0);
	material = new Material(Shader::Load("physical/gpu_picking.vs","physical/gpu_picking.fs"));
}

Node* Picking::Pick(unsigned int x, unsigned int y) 
{
	if (!enable)
		return nullptr;
	float* pixel = new float[4]{0};
	glBindFramebuffer(GL_READ_FRAMEBUFFER, colorbuffer->framebufferId);
	// glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glReadPixels(x, y, 1,1, GL_RGBA, GL_FLOAT, pixel);
	Colorf color = Colorf(pixel[0],pixel[1],pixel[2],pixel[3]);
	unsigned int identify = Convert2Identify(color);
	delete[] pixel;
	glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
	return (Node*)MeshRenderer::GetMeshRenderer(identify);
}

Colorf Picking::Convert2Color(unsigned int identify) 
{
	int r = (identify & 0x000000FF) >> 0;
	int g = (identify & 0x0000FF00) >> 8;
	int b = (identify & 0x00FF0000) >> 16;
	return Colorf(r / 255.0f, g / 255.0f, b / 255.0f, 1.0f);
}

unsigned int Picking::Convert2Identify(Colorf color) 
{
	return color.r * 255 + color.g * 255 + color.b * 255;
}

void Picking::Render(std::function<void()> func) 
{
	if (!enable)
		return;
	colorbuffer->Bind();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	if( nullptr != func )
		func();
	colorbuffer->Unbind();
}