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
			float nearClip;
			float farClip;
		};
		struct OrthographicSetting
		{
			float nearClip;
			float farClip;
		};
	public:
		Transform* transform;
		Type cameraType;
		PerspectiveSetting perspectiveSetting;
		OrthographicSetting orthographicSetting;

	public:
		void LookAt(const Node* target);
		void LookAt(const Vector3* target);
	};
}