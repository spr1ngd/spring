#pragma once
#include "behaviour.h"

namespace spring 
{
	class GameObject;
	class Camera;
	namespace editor
	{
		class ThirdPlayerCamera : public Behaviour
		{
		private:
			Camera* camera = nullptr;

		public:
			GameObject* target = nullptr;
			float distanceWithTarget;


			ThirdPlayerCamera();
			~ThirdPlayerCamera() override;

			void Awake() override;
			void Update() override;
			void Destroy() override;

			TypeInfo GetTypeInfo() override
			{
				if (nullptr == this->typeInfo)
					this->typeInfo = new TypeInfo("ThirdPlayerCamera");
				return *this->typeInfo;
			}
		};
	}
}