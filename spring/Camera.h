#pragma once
#include "node.h"
#include "transform.h"
#include "vector3.h"
#include "color.h"

namespace spring 
{
	class Camera : public Node
	{
	public:
		enum Type
		{
			Perspective,
			Orthographic
		};

		enum ClearFlag
		{
			None,
			SolidColor,
			Depth,
			Skybox
		};

		spring::Color background;
		Vector3 center = Vector3::zero;
		Vector3 direction;
		ClearFlag clearFlag = ClearFlag::SolidColor;
		Type cameraType = Type::Perspective;
		float fov = 60.0f;
		float nearClip = 0.1f;
		float farClip = 1000.0f; 
		static Camera*main;
	public:
		Camera();
		void LookAt(const Node* target);
		void LookAt(const Vector3* target);
		void Render();
	};
} 