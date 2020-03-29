#pragma once

#include "behaviour.h"

namespace spring 
{
	// ��Ҫ���������ڳ����г䵱�������ɹ��ر��Node�ڵ㣬�Դ����ű�����
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