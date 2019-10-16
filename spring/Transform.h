#pragma once
#include "glm/glm.hpp"
#include "node.h"
#include "vector3.h"
#include "matrix4x4.h"
#include "quaternion.h"

namespace spring
{ 
	class Transform : Node
	{
	private:
		Vector3 up = Vector3::up;
		Vector3 right = Vector3::right;
		Vector3 forword = Vector3::forward;

		Matrix4x4 rotationMatrix = Matrix4x4::indentity;
	public: 
		Vector3 position = Vector3::zero;
		Vector3 scale = Vector3::one;
		Vector3 eulerangle = Vector3::zero;

		Quaternion quaternion = Quaternion::indentity;
	public:
		Transform();

		Vector3 getForword();
		Vector3 getBack();
		Vector3 getUp();
		Vector3 getDown();
		Vector3 getRight();
		Vector3 getLeft();

		void SetEulerangle(Vector3 eulerangle);
		const Vector3 GetEulerangle();

		void LookAt(Vector3 target,bool isLocal = true);
		void RotateAround(Vector3 axis,float angle);
	};
}