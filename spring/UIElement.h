#pragma once
#include "rect.h"
#include "meshrenderer.h"

namespace spring 
{
	namespace ui 
	{
		class UIElement : public MeshRenderer
		{
		protected:
		public:
			UIElement();
			Rect* rect;
			void Render() override;
		};
	}
}