#include "uielement.h"

using namespace spring;
using namespace spring::ui;

UIElement::UIElement()
{
	this->rectTransform = new RectTransform();
	this->rectTransform->transform = this->transform;
}

void UIElement::GenerateMesh() 
{

}

void UIElement::Render() 
{
	this->material->shader->setColor(MAIN_COLOR, this->color);
	MeshRenderer::Render();
}