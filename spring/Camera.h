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
		struct PerspectiveSetting 
		{
			float nearClip = 0.1f;
			float farClip = 1000.0f;
		};
		struct OrthographicSetting
		{
			float nearClip = 0.1f;
			float farClip = 1000.0f;
		};
	public:
		Transform* transform;
		Vector3* center;
		Vector3* direction;
		Type cameraType = Type::Perspective;
		float fov = 60.0f;
		float nearClip = 0.1f;
		float farClip = 1000.0f;
		PerspectiveSetting perspectiveSetting;
		OrthographicSetting orthographicSetting;

	public:
		Camera();
		void LookAt(const Node* target);
		void LookAt(const Vector3* target);
		void Render(Model* model );
	};
}
