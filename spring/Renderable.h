#pragma once
#include <map>
#include <vector>
#include <iostream> 
#include "console.h"

using namespace std;

namespace spring 
{
	class Renderable 
	{
	private:
		unsigned long instanceId;
		unsigned int renderOrder = 2000;

		static unsigned long renderCounts;
		static std::vector<Renderable*> objects;

		void Insert( Renderable* object ) 
		{
			int insertIndex = 0;
			for (Renderable* item : objects)
			{
				if (item->renderOrder >= object->renderOrder) 
					break;
				insertIndex++;
			}
			this->objects.insert(objects.begin() + insertIndex, object);
		}
	public:
		bool drawAxis = false;
	public:
		Renderable() 
		{
			this->instanceId = ++renderCounts;
			this->Insert(this);
		}
		~Renderable()
		{
			int removeIndex = 0;
			for (Renderable* item : objects) 
			{
				if (item->instanceId == this->instanceId)
					break;
				removeIndex++;
			}
			this->objects.erase(this->objects.begin() + removeIndex);
		}

		void setRenderOrder(unsigned int renderOrder);
		unsigned int getRenderOrder();

		virtual void Render() = 0;
		static void Draw();
		static void Draw(unsigned int minOrder, unsigned int maxOrder);
	};
}