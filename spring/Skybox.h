#pragma once
#include "node.h"
#include "material.h"
#include "transform.h"
#include "renderable.h"

namespace spring 
{
	class Skybox : public Node ,public Renderable
	{
	public:
		Transform* transform;
		Material* material;
		Skybox(const char* skyboxName , Material* material = nullptr) 
		{
			this->transform = new Transform();
			this->name = skyboxName;
			this->material = material;
		};

		// todo : create cube mesh by Primitive object.
		void Render();
	};
}