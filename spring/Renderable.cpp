#include "renderable.h"
#include <iostream>

using namespace std;
using namespace spring;

unsigned long Renderable::renderCounts = 0;
std::map<unsigned long, Renderable*> Renderable::objects;

void Renderable::Draw()
{
	for (unsigned int i = 0; i < objects.size(); i++) 
	{
		auto object = objects[i];
		object->Render();
		std::cout << "rendering " << object->instanceId << std::endl;
	}
}