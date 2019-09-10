#pragma once
#include "node.h"
#include "transform.h"
#include "vector3.h"
#include "model.h"

namespace spring 
{
	class Camera : public Node
	{
		enum Type
		{
			Perspective,
			Orthographic
		}; 

	public:
		Transform* transform;
		Vector3* center;
		Vector3* direction;
		Type cameraType = Type::Perspective;
		float fov = 60.0f;
		float nearClip = 0.1f;
		float farClip = 1000.0f; 
		static Camera*main;
	public:
		Camera();
		void LookAt(const Node* target);
		void LookAt(const Vector3* target);
		void Render(Model* model );
	};
}
