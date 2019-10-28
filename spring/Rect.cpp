#include "rect.h"

using namespace std;
using namespace spring;
using namespace spring::ui;

Rect::Rect(float x, float y, float width, float height)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	float halfWidth = width / 2.0f;
	float halfHeight = height / 2.0f;
	this->center = Vector2(x + halfWidth, y + halfHeight);
	this->position = Vector2(x + halfWidth, y + halfHeight);
}