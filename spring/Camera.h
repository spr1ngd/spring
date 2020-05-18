#pragma once
#include <vector>
#include "node.h"
#include "matrix4x4.h"
#include "vector3.h"
#include "color.h"

namespace spring 
{
	class FrameBuffer;
	class Camera : public Node
	{
	private:
		glm::mat4 ViewMatrix;
		glm::mat4 ProjectionMatrix;
		glm::mat4 Projection2DMatrix;
		glm::mat4 ViewProjectionMatrix;

		static void CachingCamera(Camera* camera);

	public:
		static std::vector<Camera*> cameras;
		static Camera* main;
		static Camera* current;

		enum CameraType
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
		CameraType cameraType = CameraType::Perspective;
		LayerMask* cullingMask;
		float fov = 60.0f;
		float nearClip = 0.001f;
		float farClip = 1000.0f; 

		FrameBuffer* framebuffer = nullptr;
		FrameBuffer* renderTarget = nullptr;
		bool enableHDR = false;

	public:
		Camera();

		void LookAt(const Node* target);
		void LookAt(const Vector3* target);

		const glm::mat4& GetViewMatrix();
		const glm::mat4& GetProjectionMatrix();
		const glm::mat4& Get2DProjection();
		const glm::mat4& GetViewProjectionMatrix();
		void Update();
		void Render();
		void Destroy() override;
	};
} 