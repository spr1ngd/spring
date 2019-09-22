#include "renderable.h"

using namespace std;
using namespace spring;

unsigned long Renderable::renderCounts = 0;
vector<Renderable*> Renderable::objects;

void Renderable::Draw()
{ 
	for (unsigned int i = 0; i < objects.size(); i++)
	{
		auto object = objects[i];
		object->Render();
	}
}