#pragma once
#include "framebuffer.h"
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
		bool awaked = false;
		bool enabled = true;

		Behaviour();
		~Behaviour() override;
		
		virtual void Awake();
		virtual void Update();
		void Destroy() override;

		virtual void OnGUI();
		virtual void OnPreRender();
		virtual void OnPostRender();

		TypeInfo GetTypeInfo() override
		{
			if (nullptr == this->typeInfo)
				this->typeInfo = new TypeInfo("Behaviour");
			return *this->typeInfo;
		}
	};
}