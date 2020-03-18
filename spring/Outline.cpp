#include "outline.h"
#include "picking.h"
#include "postprocessing.h"

using namespace spring;

Outline::Outline() 
{

}

void Outline::Render(std::function<void()> func) 
{	
	if (!PostProcessing::postprocessing->enabled)
		return;
	float minX = 0.0f;
	float maxX = minX + Screen::width * 0.6f;
	float minY = 80.0f;
	float maxY = minY + Screen::height * 0.6f;
	float mouseX = Input::mousePosition.x;
	float mouseY = Input::mousePosition.y;

	//if ((mouseX >= minX && mouseX <= maxX) && (mouseY >= minY && mouseY <= maxY) )
	{
		Node* selected = Picking::Pick(mouseX, mouseY);
		//Node* selected = Picking::Pick((mouseX - minX) / 0.6f, (mouseY - minY) / 0.6f);
		if (nullptr != selected)
		{
			this->buffer->Bind();
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
			MeshRenderer* meshrenderer = (MeshRenderer*)selected;
			Material* originMaterial = meshrenderer->material;
			this->outlineMaterial->shader->setColor("outlineColor", this->outlineColor);
			this->outlineMaterial->shader->setFloat("outlineWidth", this->outlineWidth);
			meshrenderer->material = this->outlineMaterial;
			Camera::current = Camera::main;
			// Camera::current->Render();
			meshrenderer->Render();
			meshrenderer->material = originMaterial;
			this->buffer->Unbind();

			this->originBuffer->Bind();
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			Camera::current = Camera::main;
			// Camera::current->Render();
			meshrenderer->Render();
			this->originBuffer->Unbind();
		}
		else 
		{
			this->buffer->Bind();
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
			this->buffer->Unbind();

			this->originBuffer->Bind();
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			this->originBuffer->Unbind();
		}
	}
}