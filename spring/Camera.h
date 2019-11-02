#pragma once
#include <vector>
#include "node.h"
#include "matrix4x4.h"
#include "transform.h"
#include "vector3.h"
#include "color.h"

namespace spring 
{
	class Camera : public Node
	{
	private:
		static void CachingCamera(Camera* camera);

	public:
		static std::vector<Camera*> cameras;
		static Camera* main;

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
		Layer culling = Layer::Everything;
		float fov = 60.0f;
		float nearClip = 0.1f;
		float farClip = 1000.0f; 

	public:
		Camera();

		void LookAt(const Node* target);
		void LookAt(const Vector3* target);

		glm::mat4 GetViewMatrix();
		glm::mat4 GetProjectionMatrix();
		void Render();
		void Destroy() override;
	};
} 