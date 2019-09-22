#pragma once
#include <vector>
#include "mesh.h"
#include "transform.h"
#include "meshrenderer.h"
#include "material.h"

namespace spring 
{
	class AxisHelper
	{
		// todo : generate a axis in scene 
		// todo : axis helper will translate/rotate through transform data.
		// todo : renderable composite this object.
	private:
		Material* material;
		MeshRenderer* meshRenderer;
	public:
		enum Mode 
		{
			Axis,
			Rotate,
			Scale
		};
		Mode mode = Mode::Axis;
	private:

		void RenderAxis();
		void RenderRotator();
		void RenderScaler();
	public:
		AxisHelper();

		void Render();
	};
}