#include "picking.h"

using namespace spring;

bool Picking::enable;
GameObject* Picking::selected;
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

void Picking::Pick() 
{
	if (enable == false)
		return;
	float minX = 10.0f;
	float maxX = minX + Screen::width * 0.6f;
	float minY = Screen::height - 50.0f - Screen::height * 0.6f - 30.0f;
	float maxY = minY + Screen::height * 0.6f;
	float mouseX = Input::mousePosition.x;
	float mouseY = Input::mousePosition.y;
	if ((mouseX >= minX && mouseX <= maxX) && (mouseY >= minY && mouseY <= maxY))
	{
		Node* node = Picking::Pick((mouseX - minX) / 0.6f, (mouseY - minY) / 0.6f);
		if (nullptr != node) selected = node->gameobject;
		else selected = nullptr;
	}
}

Node* Picking::Pick(unsigned int x, unsigned int y) 
{
	if (!enable)
		return nullptr;
	Colorf color = pickBuffer->ReadPixel(x, y);
	unsigned int identify = Convert2Identify(color);
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