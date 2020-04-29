#pragma once
#include "glm/glm.hpp"
#include "quaternion.h"
#include "vector3.h"
#include "matrix4x4.h"

namespace spring
{ 
	class GameObject;
	class Transform
	{
	private:
		bool transformChangedInThisFrame = true;
		Vector3 localPosition = Vector3::zero;		

		glm::mat4 mMatrix;
		glm::mat4 nmMatrix;

		void RecalculateTransform();

	public: 
		Vector3 up = Vector3::up;
		Vector3 right = Vector3::right;
		Vector3 forword = Vector3::forward;

		Matrix4x4 rotationMatrix = Matrix4x4::indentity;
		Quaternion rotation = Quaternion::indentity;

		Vector3 eulerangle = Vector3::zero;
		Vector3 scale = Vector3::one;
		Vector3 position = Vector3::zero;

		GameObject* gameobject = nullptr;

		Transform();

		void SetEulerangle(Vector3 eulerangle);
		const Vector3& GetEulerangle();

		void SetRotation(Quaternion rotation);
		const Quaternion& GetRotation();

		void SetPosition(Vector3 position);
		const Vector3& GetPosition();

		void SetLocalPosition(Vector3 localPosition);
		Vector3 GetLocalPosition();

		void SetScale(Vector3 scale);
		const Vector3& GetScale();

		void LookAt(Vector3 target,bool isLocal = true);
		void Rotate(Vector3 axis,float angle);
		void RotateAround(Vector3 point,Vector3 axis,float angle);

		glm::mat4& GetModelMatrix();
		glm::mat4& GetNMMatrix();
	};
}