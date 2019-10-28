#pragma once
#include "node.h"
#include "rect.h"
#include "renderable.h"
#include "meshrenderer.h"

namespace spring 
{
	namespace ui 
	{
		class UIElement : public MeshRenderer
		{
		protected:
			UIElement();
		public:
			Rect* rect;
			void Render() override;
		};
	}
}