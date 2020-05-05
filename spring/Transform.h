#pragma once
#include <vector>
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
		Transform* parent = nullptr;
		std::vector<Transform*> children;

		bool transformChangedInThisFrame = true;
		Quaternion rotation = Quaternion::indentity;
		Vector3 localPosition = Vector3::zero;
		Vector3 localScale = Vector3::one;
		Vector3 localEulerangle = Vector3::zero;

		glm::mat4 mMatrix;
		glm::mat4 nmMatrix;
		Matrix4x4 rotationMatrix = Matrix4x4::indentity;

		void RecalculateTransform();

	public: 
		Vector3 up = Vector3::up;
		Vector3 right = Vector3::right;
		Vector3 forword = Vector3::forward;

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

		void SetLocalScale(Vector3 localScale);
		const Vector3& GetLocalScale();

		void SetLocalEulerangle(Vector3 localEulerangle);
		const Vector3& GetLocalEulerangle();

		void LookAt(Vector3 target,bool isLocal = true);
		void Rotate(Vector3 axis,float angle);
		void RotateAround(Vector3 point,Vector3 axis,float angle);

		void SetParent(Transform& parent);
		Transform* GetParent();

		Transform* QueryChild(unsigned int childIndex);
		Transform* QueryChild(const char* childPath);
		unsigned int GetChildCount();

		glm::mat4& GetModelMatrix();
		glm::mat4& GetNMMatrix();
	};
}