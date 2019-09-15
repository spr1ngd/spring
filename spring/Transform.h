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

		Vector3 forword;
		Vector3 back;
		Vector3 top;
		Vector3 bottom;
		Vector3 right;
		Vector3 left;

	public:
		Transform();
		void LookAt(Vector3 target,Vector3 worldUp = Vector3::up);
	};
}