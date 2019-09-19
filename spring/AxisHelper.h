#pragma once
#include <vector>
#include "mesh.h"
#include "transform.h"

namespace spring 
{
	class AxisHelper
	{
		// todo : generate a axis in scene 
		// todo : axis helper will translate/rotate through transform data.
		// todo : renderable composite this object.

	public:
		enum Mode 
		{
			Axis,
			Rotate,
			Scale
		};
		Mode mode = Mode::Axis;
		Transform* transform;
	private:
		Mesh* mesh;

		void RenderAxis();
		void RenderRotator();
		void RenderScaler();
	public:
		AxisHelper();

		void Render();
	};
}