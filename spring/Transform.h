#pragma once
#include "glm/glm.hpp"
#include "quaternion.h"
#include "vector3.h"
#include "matrix4x4.h"

namespace spring
{ 
	class Transform
	{
	public: 
		Matrix4x4 rotationMatrix = Matrix4x4::indentity;
		Vector3 up = Vector3::up;
		Vector3 right = Vector3::right;
		Vector3 forword = Vector3::forward;
		Vector3 position = Vector3::zero;
		Vector3 eulerangle = Vector3::zero;
		Quaternion rotation = Quaternion::indentity;
		Vector3 scale = Vector3::one;

		Transform();

		void SetEulerangle(Vector3 eulerangle);
		const Vector3& GetEulerangle();

		void SetRotation(Quaternion rotation);
		const Quaternion& GetRotation();

		void SetPosition(Vector3 position);
		const Vector3& GetPosition();

		void SetScale(Vector3 scale);
		const Vector3& GetScale();

		void LookAt(Vector3 target,bool isLocal = true);
		void Rotate(Vector3 axis,float angle);
		void RotateAround(Vector3 point,Vector3 axis,float angle);
	};
}