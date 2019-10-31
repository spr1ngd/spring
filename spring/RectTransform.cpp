#include "recttransform.h"
#include "console.h"

using namespace spring;

RectTransform::RectTransform() 
{
	this->size = Vector2::one;
	this->pivot = Vector2::half;
}

void RectTransform::SetPivot(Vector2 pivot) 
{
	auto position = this->transform->GetPosition();
	float left = position.x - this->size.x * this->pivot.x;
	float bottom = position.y - this->size.y * this->pivot.y;

	this->pivot = pivot;
	position = Vector3(left + this->size.x * this->pivot.x, bottom + this->size.y * this->pivot.y, 0.0f);
	this->transform->SetPosition(position);
}