#pragma once
#include <map>
#include <vector>
#include <iostream> 
#include <functional>
#include "console.h"

using namespace std;

namespace spring 
{
	class MeshRenderer;
	class ParticleRenderer;
	class Renderable
	{
	private:
		unsigned long rendererId;
		unsigned int renderOrder = 2000;

		static unsigned long renderCounts;
		static std::vector<Renderable*> objects;
		static std::vector<MeshRenderer*> meshRenderers;
		static std::vector<ParticleRenderer*> particleRenderers;

		void Insert( Renderable* object ) 
		{
			// todo : Ϊ�˸�renderers����
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
			this->rendererId = ++renderCounts;
			this->Insert(this);
		}
		~Renderable()
		{
			int removeIndex = 0;
			for (Renderable* item : objects) 
			{
				if (item->rendererId == this->rendererId)
					break;
				removeIndex++;
			}
			this->objects.erase(this->objects.begin() + removeIndex);
		}

		void setRenderOrder(unsigned int renderOrder);
		unsigned int GetRenderOrder();
		unsigned int GetRenderableId();

		virtual void Render() = 0;
		static void Draw();
		static void Draw(int layers);
		static void Draw(int layers, std::function<void(MeshRenderer*)> func);

		static Renderable* GetRender(unsigned int renderableId);

		static void CacheRenderer(MeshRenderer* meshRenderer);
		static void CacheRenderer(ParticleRenderer* particleRenderer);
	};
}