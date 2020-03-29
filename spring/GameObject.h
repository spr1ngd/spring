#pragma once

#include "behaviour.h"

namespace spring 
{
	// 主要作用用来在场景中充当容器，可挂载别的Node节点，以触发脚本功能
	class GameObject : public Behaviour
	{
	public:
		// 1. extract visible from node to gameobject.
		// 2. extract layer field from node to gameobject.
		// 3. extract physical hierarchy structure from node to gameobject. node is just a base class.

		GameObject();
		GameObject(const char* name);
	};
}