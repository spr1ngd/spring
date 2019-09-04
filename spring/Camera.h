#pragma once
#include "node.h"
#include "transform.h"
#include "vector3.h"

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
		Type cameraType = Type::Perspective;
		PerspectiveSetting perspectiveSetting;
		OrthographicSetting orthographicSetting;

	public:
		void LookAt(const Node* target);
		void LookAt(const Vector3* target);
	};
}
