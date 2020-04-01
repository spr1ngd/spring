#pragma once

#include <vector>
#include "object.h"
#include "transform.h"

using namespace std;

namespace spring 
{
	// 主要作用用来在场景中充当容器，可挂载别的Node节点，以触发脚本功能
	// todo : 不应该继承behaviour，直接继承Object更好 
	class GameObject : public Object
	{
	private:
		static std::vector<GameObject*> gameobjects;

		static void AddGameObject(GameObject* gameobject);
		static void RemoveGameObject(GameObject* gameobject);
	public:
		// 1. extract visible from node to gameobject.
		// 2. extract layer field from node to gameobject.
		// 3. extract physical hierarchy structure from node to gameobject. node is just a base class.
		bool visible = true;
		Transform transform; // only store position/rotation/scale/eulerangle data

		std::vector<GameObject*> children;
		GameObject* parent;

		GameObject();
		GameObject(const char* name);
	};
}