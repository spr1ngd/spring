#pragma once
#include <map>
#include <glm/glm.hpp>
#include "node.h"
#include "color.h"
#include "transform.h"
#include "vector3.h"
#include "vector4.h"
#include "framebufferobject.h"
#include "layer.h"

using namespace std;

namespace spring 
{
	class Light : public Node
	{
	public:
		enum Type 
		{
			Directional,
			Spot,
			Point,
			Area
		};
		enum RenderMode
		{
			Auto,
			Pixel,
			Vertex
		};
		enum ShadowType 
		{
			NoShadow,
			HardShadow,
			SoftShadow
		};

	public:
		static map<const long, Light*> lights;
		static Light* main;

		Light::RenderMode renderMode = Light::RenderMode::Auto;
		Light::Type type = Light::Type::Directional;
		Color color = Color::white;
		float intensity = 1.0f;
		// only work in spot and point mode
		float range = 10.0f;
		float constant = 1.0f;
		float linear = 0.09f;
		float quadratic = 0.032f;
		// only work in spot light mode
		float spotAngle = 25.0f;
		float outterAngle = 70.0f;

		// shadow setting
		LayerMask* cullingMask;
		ShadowType shadowType = ShadowType::HardShadow;
		FrameBufferObject* shadow;

	public:
		Light();

		void CastShadow();
		// glm::mat4 GetViewMatrix();
	};
}