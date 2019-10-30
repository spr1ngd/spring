#include "uielement.h"

using namespace spring;
using namespace spring::ui;

UIElement::UIElement()
{
	this->rect = new Rect(0.0f, 0.0f, 100.0f, 100.0f);
}

void UIElement::Render() 
{
	this->material->shader->setColor(MAIN_COLOR, this->color);
	MeshRenderer::Render();
}