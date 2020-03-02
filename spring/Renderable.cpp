#include <algorithm>
#include "node.h"
#include "meshrenderer.h"
#include "console.h"

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
}

unsigned int Renderable::GetRenderOrder() 
{
	return this->renderOrder;
}

unsigned int Renderable::GetRenderableId()
{
	return this->rendererId;
}

void Renderable::Draw()
{ 
	for (unsigned int i = 0; i < objects.size(); i++)
	{
		auto object = objects[i];
		object->Render();
	}
}

void Renderable::Draw(unsigned int layerCount, unsigned int* layers)
{
	if (layerCount <= 0)
		return;
	for (unsigned int i = 0; i < objects.size(); i++)
	{
		auto object = objects[i];
		for (unsigned int j = 0; j < layerCount; j++)
		{
			unsigned int layer = layers[j];
			auto node = (MeshRenderer*)object;
			if (node->layer == layer) 
			{
				object->Render();
				break;
			}
		}
	}
}

void Renderable::Draw(unsigned int layerCount, unsigned int* layers , std::function<void(MeshRenderer*)> func)
{
	if (layerCount <= 0)
		return;
	for (unsigned int i = 0; i < objects.size(); i++)
	{
		auto object = objects[i];
		for (unsigned int j = 0; j < layerCount; j++)
		{
			unsigned int layer = layers[j];
			auto node = (MeshRenderer*)object;
			if (node->layer == layer)
			{
				if (nullptr != func)
					func(node);
				break;
			}
		}
	}
}

Renderable* Renderable::GetRender(unsigned int renderableId)
{
	for (auto item = objects.begin();item != objects.end();item++)
	{
		Renderable* render = *item;
		if (render->rendererId == renderableId)
			return render;
	}
	return nullptr;
}