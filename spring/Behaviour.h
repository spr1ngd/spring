#pragma once
#include "framebufferobject.h"
#include "material.h"
#include "node.h"
#include <map>

namespace spring 
{
	class Behaviour : public Node
	{
	private:
		static unsigned long count;
	public:
		static std::map<const unsigned long, Behaviour*> behaviours; 
	public:
		Behaviour();
		virtual void Awake();
		virtual void Update();
		void Destroy() override;

		virtual void OnGUI();
		virtual void OnPreRender();
		virtual void OnPostRender();
	};
}