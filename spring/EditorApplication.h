#pragma once
#include "behaviour.h"

namespace spring
{
	class GameObject;
	namespace editor
	{
		class EditorApplication : public Behaviour
		{
			// 1. generate editor axis 
			// 2. generate editor rotate
			// 3. generate editor scaler
			// 4. generate 3d space guide axis

			// 将gameapp中部分抽离到这里
		private:
			GameObject* axisGizmos = nullptr;
			GameObject* rotateGizmos = nullptr;
			GameObject* scaleGizmos = nullptr;

			void Awake() override;
			void Update() override;
			void Destroy() override;
		};
	}
}