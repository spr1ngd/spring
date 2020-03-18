#include "picking.h"

using namespace spring;

bool Picking::enable;
FrameBuffer* Picking::pickBuffer;
Material* Picking::material;

Picking::Picking()
{

}

void Picking::Initialize() 
{
	if (!enable)
		return;
	pickBuffer = new FrameBuffer(Screen::width,Screen::height,ColorFormat::RGB24);
	pickBuffer->Initialize();
	material = new Material(Shader::Load("physical/gpu_picking.vs","physical/gpu_picking.fs"));
}

Node* Picking::Pick(unsigned int x, unsigned int y) 
{
	if (!enable)
		return nullptr;
	unsigned char pixel[3];
	pickBuffer->Bind();
	// glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);
	PRINT_ERROR("pick color (%d,%d,%d)",pixel[0], pixel[1], pixel[2]);
	Color color = Color(pixel[0], pixel[1], pixel[2],0);
	unsigned int identify = Convert2Identify(color);
	pickBuffer->Unbind();
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

unsigned int Picking::Convert2Identify(Color color) 
{
	return color.r + color.g + color.b;
}

void Picking::Render(std::function<void()> func) 
{
	if (!enable)
		return;
	pickBuffer->Bind();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	if( nullptr != func )
		func();
	pickBuffer->Unbind();
}