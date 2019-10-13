#pragma once
#include "glm/glm.hpp"
#include "node.h"
#include "vector3.h"

namespace spring
{ 
	class Transform : Node
	{
	private:
		Vector3 up = Vector3::up;
		Vector3 right = Vector3::right;
		Vector3 forword = Vector3::forward;
	public:
		Vector3 Forword = Vector3::forward;
		Vector3 position = Vector3::zero;
		Vector3 scale = Vector3::one;
		Vector3 eulerangle = Vector3::zero; // todo : i need to learn why unity engine use Quaternion.rotation and Vector3.eulerangle.
	public:
		Transform();

		Vector3 getForword();
		Vector3 getBack();
		Vector3 getUp();
		Vector3 getDown();
		Vector3 getRight();
		Vector3 getLeft();

		void LookAt(Vector3 target,bool isLocal = true);
		void RotateAround(Vector3 point,Vector3 axis,float angel);
	};
}