#pragma once
#include "node.h"
#include "vector3.h"

namespace spring
{
	class Transform : Node
	{
	public:
		Vector3 position;
		Vector3 scale;
		Vector3 eulerangle; // todo : i need to learn why unity engine use Quaternion.rotation and Vector3.eulerangle.

		static void Destroy();
	};
}