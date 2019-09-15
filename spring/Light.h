#pragma once
#include <map>
#include "node.h"
#include "color.h"
#include "transform.h"
#include "vector3.h"

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
	private:
		static map<const long, Light*> lights;
	public:
		Light::RenderMode renderMode = Light::RenderMode::Auto;
		Light::Type type = Light::Type::Directional;
		Color color = Color::white;
		float intensity = 1.0f;
		Transform* transform;
		// todo : light shadow settings

		static Light* main;

	public:
		Light();
	};
}