#include "renderable.h"
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
		// todo: avoid dynamic cast
		MeshRenderer* renderer = dynamic_cast<MeshRenderer*>(objects[i]);
		int layer = renderer->gameobject->layer;
		if ((layers & layer) == layer)
			renderer->Render();
	}
}

void Renderable::Draw(int layers , std::function<void(MeshRenderer*)> func)
{
	for (unsigned int i = 0; i < objects.size(); i++)
	{ 
		// todo: avoid dynamic cast
		MeshRenderer* renderer = dynamic_cast<MeshRenderer*>(objects[i]);
		int layer = renderer->gameobject->layer;
		if ((layers & layer) == layer)
		{
			if (nullptr != func)
				func(renderer);
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

void Renderable::CacheRenderer(ParticleRenderer* particleRenderer) 
{

}

void Renderable::CacheRenderer(MeshRenderer* meshRenderer) 
{

}