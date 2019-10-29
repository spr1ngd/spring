#include "gui.h"

using namespace spring;
using namespace spring::ui;

std::vector<UIElement*> GUI::uiElements;

Image* GUI::DrawImage(Rect rect)
{
	Image* image = new Image();
	image->rect = &rect;
	image->GenerateMesh();
	return image;
}