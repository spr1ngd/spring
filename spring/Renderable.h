#pragma once
#include <map>
#include <iostream>

namespace spring 
{
	class Renderable 
	{
	private:
		static unsigned long renderCounts;
		unsigned long instanceId;
		static std::map<unsigned long, Renderable*> objects;
	public:
		Renderable() 
		{
			this->instanceId = ++renderCounts;
			objects.insert(std::pair<unsigned long,Renderable*>(this->instanceId,this));
		}
		~Renderable()
		{
			auto item = objects.find(this->instanceId);
			if (item != objects.end())
				objects.erase(this->instanceId);
		}
		virtual void Render() = 0;
		static void Draw();
	};
}