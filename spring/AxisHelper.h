#pragma once
#include <vector>
#include "behaviour.h"
#include "space.h"

namespace spring 
{
	class AxisHelper : public Behaviour
	{
	public:
		enum EditorGizmosMode
		{
			EditMode_Move,
			EditMode_Rotate,
			EditMode_Scale
		};
		enum AxisMode
		{
			None,
			X,
			Y,
			Z
		};
	private:
		Transform* target;
		CoordinateSpace space = CoordinateSpace::World;

		GameObject* axisGizmos = nullptr;
		GameObject* rotateGizmos = nullptr;
		GameObject* scaleGizmos = nullptr;

		bool editing = false;
		EditorGizmosMode gizmosMode = EditorGizmosMode::EditMode_Move;
		AxisMode currentEditAxis = AxisMode::None;

	public: 
		float moveSpeed = 0.05f;
		float scaleSpeed = 0.01f;
		float rotateSpeed = 1.0f;

		AxisHelper();
		void Awake() override;
		void Update() override;
		void Destroy() override;
		void SetTarget(Transform* target);
		void SetAxisMode(AxisHelper::EditorGizmosMode mode);
		TypeInfo GetTypeInfo() override 
		{
			if (nullptr == this->typeInfo)
				this->typeInfo = new TypeInfo("AxisHelper");
			return *this->typeInfo;
		}
	};
}