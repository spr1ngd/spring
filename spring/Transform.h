#pragma once
#include "node.h"
#include "vector3.h"

namespace spring
{
	class Transform : Node
	{
	public:
		Vector3 position = Vector3::zero;
		Vector3 scale = Vector3::one;
		Vector3 eulerangle = Vector3::zero; // todo : i need to learn why unity engine use Quaternion.rotation and Vector3.eulerangle.

		static void Destroy();
	};
}