#pragma once
#include "camera.h"
#include "behaviour.h"

namespace spring 
{
	namespace editor 
	{
		class FirstPlayerCamera : public Behaviour
		{
		private:
			Camera* camera;
		public:
			float moveSpeed = 1.0f;
			float rotateSpeed = 0.25f;

			FirstPlayerCamera();

			void Awake() override;
			void Update() override;

			TypeInfo GetTypeInfo() override
			{
				if (nullptr == this->typeInfo)
					this->typeInfo = new TypeInfo("FirstPlayerCamera");
				return *this->typeInfo;
			}
		};
	}
}
