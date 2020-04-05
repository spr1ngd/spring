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

void Renderable::Draw(int layers)
{
	for (unsigned int i = 0; i < objects.size(); i++)
	{
		auto object = objects[i];
		try
		{
			MeshRenderer* renderer = dynamic_cast<MeshRenderer*>(object);
			int layer = renderer->gameobject->layer;
			if ((layers & layer) == layer)
				renderer->Render();
		}
		catch (bad_cast)
		{
			PRINT_ERROR("cast renderable object to meshrenderer failed.");
		}
	}
}

void Renderable::Draw(int layers , std::function<void(MeshRenderer*)> func)
{
	for (unsigned int i = 0; i < objects.size(); i++)
	{
		auto object = objects[i];
		try
		{
			MeshRenderer* renderer = dynamic_cast<MeshRenderer*>(object);
			int layer = renderer->gameobject->layer;
			if ((layers & layer) == layer)
			{
				if (nullptr != func)
					func(renderer);
			}
		}
		catch (bad_cast)
		{
			PRINT_ERROR("cast renderable object to meshrenderer failed.");
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