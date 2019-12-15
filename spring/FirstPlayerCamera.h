#pragma once
#include "camera.h"
#include "behaviour.h"

namespace spring 
{
	namespace editor 
	{
		class FirstPlayerCamera : Behaviour
		{
		private:
			Camera* camera;
		public:
			float moveSpeed = 1.0f;

			void Awake() override;
			void Update() override;
		};
	}
}
