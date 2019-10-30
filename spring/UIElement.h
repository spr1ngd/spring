#pragma once
#include "color.h"
#include "rect.h"
#include "meshrenderer.h"

namespace spring 
{
	namespace ui 
	{
		class UIElement : public MeshRenderer
		{
		public:
			Color color = Color::white;
		public:
			UIElement();
			Rect* rect;

			void Render() override;
		};
	}
}