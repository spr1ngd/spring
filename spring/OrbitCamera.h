#pragma once
#include "behaviour.h"
#include "vector3.h"
#include "camera.h"

namespace spring
{
	namespace editor 
	{
		class OrbitCamera : public Behaviour
		{
		private: 
			bool enableZoom = false;
			bool enableRotate = false;
			bool enablePan = false;
			bool enableControl = false; // control camera through keyboard  

			void Zoom();
			void Rotate();
			void Pan();
		public:
			Camera* camera;
			Vector3 target;

			float rotateSpeed = 2.0f;
			float zoomSpeed = 0.5f;
			float panSpeed = 1.0f;

			float distance = 1.0f;
			float minDistance = 0.5f;
			float maxDistance = 300.0f; 

			OrbitCamera();
			void Awake() override;
			void Update() override;
			void Destroy() override;

			TypeInfo GetTypeInfo() override
			{
				if (nullptr == this->typeInfo)
					this->typeInfo = new TypeInfo("OrbitCamera");
				return *this->typeInfo;
			}
		};
	}
}