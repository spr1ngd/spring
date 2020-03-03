#include "outline.h"
#include "picking.h"

using namespace spring;

Outline::Outline() 
{

}

void Outline::Render(std::function<void()> func) 
{
	this->buffer->Bind();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	if (Input::mousePosition.x <= Screen::width * 0.6f && Input::mousePosition.y <= Screen::height * 0.6f)
	{
		Node* selected = Picking::Pick(Input::mousePosition.x / 0.6f, Input::mousePosition.y / 0.6f);
		if (nullptr != selected)
		{
			MeshRenderer* meshrenderer = (MeshRenderer*)selected;
			Material* originMaterial = meshrenderer->material;
			Console::LogFormat("render out line object = {%s} ", meshrenderer->name);

			this->outlineMaterial->shader->setColor("outlineColor", this->outlineColor);
			this->outlineMaterial->shader->setFloat("outlineWidth", this->outlineWidth);
			meshrenderer->material = this->outlineMaterial;
			Camera::current = Camera::main;
			Camera::current->Render();
			meshrenderer->Render();
			meshrenderer->material = originMaterial;
		}
	}
	this->buffer->Unbind(); 
}