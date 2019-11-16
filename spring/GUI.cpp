#include "gui.h"

using namespace spring;
using namespace spring::ui;

std::vector<UIElement*> GUI::uiElements;

Image* GUI::DrawImage(Rect rect)
{
	Image* image = new Image();
	image->rectTransform->size = Vector2(rect.width,rect.height);
	float posX = rect.x + rect.width / 2.0f;
	float posY = rect.y + rect.height / 2.0f;
	image->transform->SetPosition(Vector3(posX, posY, 0.0f));
	// todo : refactor ui element base class 
	image->GenerateMesh();
	uiElements.push_back(image);
	return image;
}

Text* GUI::DrawText(Rect rect) 
{
	Text* text = new Text();
	text->rectTransform->size = Vector2(rect.width,rect.height);
	float posX = rect.x + rect.width / 2.0f;
	float posY = rect.y + rect.height / 2.0f;
	text->transform->SetPosition(Vector3(posX,posY,0.0f));
	uiElements.push_back(text);
	return text;
}