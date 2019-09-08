#pragma once
#include "behaviour.h"

namespace spring
{
	namespace editor 
	{
		class OrbitCamera : public Behaviour
		{
		public:
			OrbitCamera();
			void Awake() override;
			void Update() override;
			void Destroy() override;
		};
	}
}