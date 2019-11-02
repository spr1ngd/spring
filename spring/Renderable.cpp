#include <algorithm>
#include "renderable.h"

using namespace std;
using namespace spring;

unsigned long Renderable::renderCounts = 0;
vector<Renderable*> Renderable::objects;

void Renderable::setRenderOrder(unsigned int renderOrder) 
{
	this->renderOrder = renderOrder;
	auto sortFunc = [&](Renderable* a, Renderable* b)->bool
	{
		return a->renderOrder < b->renderOrder;
	};
	sort(this->objects.begin(), this->objects.end(), sortFunc);
	/*for (Renderable* item : objects)
		Console::LogFormat("render order %d ", item->renderOrder);*/
}

unsigned int Renderable::getRenderOrder() 
{
	return this->renderOrder;
}

void Renderable::Draw()
{ 
	for (unsigned int i = 0; i < objects.size(); i++)
	{
		auto object = objects[i];
		object->Render();
	}
}

void Renderable::Draw(unsigned int minOrder, unsigned int maxOrder)
{
	for (unsigned int i = 0; i < objects.size(); i++)
	{
		auto object = objects[i];
		if( object->renderOrder >= minOrder && object->renderOrder < maxOrder )
			object->Render();
	}
}