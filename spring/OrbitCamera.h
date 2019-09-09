#pragma once
#include "behaviour.h"
#include "vector3.h"

namespace spring
{
	namespace editor 
	{
		class OrbitCamera : public Behaviour
		{
		private: 
			bool enableZoom;
			bool enableRotate;
			bool enablePan;
			bool enableControl = false; // control camera through keyboard  

			void Zoom();
			void Rotate();
			void Pan();
			void Move();
		public:
			Vector3 target;
			float rotateSpeed = 0.2f;
			float zoomSpeed = 0.5f;
			float panSpeed = 1.0f;
			float moveSpeed = 1.0f;

			OrbitCamera();
			void Awake() override;
			void Update() override;
			void Destroy() override;
		};
	}
}