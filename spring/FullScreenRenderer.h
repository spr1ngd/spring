#pragma once
#include <vector>
#include "material.h"
#include "layer.h"
#include "springengine.h"

namespace spring
{
	class FullScreenRenderer
	{
	public:
		static std::vector<FullScreenRenderer*> renderers;

		enum FullScreenRenderType
		{
			Color,
			Depth
		};

		Material* material;
		LayerMask* cullingMask;
		FrameBufferObject* buffer;
		FullScreenRenderType type = FullScreenRenderType::Color;

	public:
		FullScreenRenderer();
		FullScreenRenderer(FullScreenRenderType type);

		void Initialize();
		void Destroy();
		void Render();
	};
}