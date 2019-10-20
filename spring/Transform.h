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
		Vector3 eulerangle = Vector3::zero;

	public: 
		Matrix4x4 rotationMatrix = Matrix4x4::indentity;
		Vector3 up = Vector3::up;
		Vector3 right = Vector3::right;
		Vector3 forword = Vector3::forward;
		Vector3 position = Vector3::zero;
		Vector3 scale = Vector3::one;

		Quaternion quaternion = Quaternion::indentity;
	public:
		Transform(); 

		void SetEulerangle(Vector3 eulerangle);
		const Vector3 GetEulerangle();

		void LookAt(Vector3 target,bool isLocal = true);
		void Rotate(Vector3 axis,float angle);
		void RotateAround(Vector3 point,Vector3 axis,float angle);
	};
}