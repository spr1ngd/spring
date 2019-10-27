#pragma once
#include "node.h"
#include "renderable.h"
// #include "meshrenderer.h"

namespace spring 
{
	namespace ui 
	{
		class UIElement : Node , Renderable //, MeshRenderer
		{
		public:
			void Render() override;
		};
	}
}